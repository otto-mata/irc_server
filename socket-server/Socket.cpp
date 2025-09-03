#include "Socket.hpp"
#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

SocketServer::SocketServer(unsigned short serverPort)
{
  _port = htons(serverPort);
  _fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (_fd < 0)
    throw std::exception();
  int optValue = 1;
  if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(optValue)) <
      0) {
    perror("SocketServer::init - setsockopt");
    close(_fd);
    throw std::exception();
  }
  ::memset(&_in, 0, sizeof(_in));
  _in.sin_addr.s_addr = INADDR_ANY;
  _in.sin_port = _port;
  _in.sin_family = AF_INET;
  if (bind(_fd, (struct sockaddr*)&_in, sizeof(_in)) < 0) {
    perror("SocketServer::init - bind");
    close(_fd);
    throw std::exception();
  }
  if (listen(_fd, BACKLOG) < 0) {
    perror("SocketServer::init - listen");
    close(_fd);
    throw std::exception();
  }
  _mustStop = false;
  std::cout << "Server started on port " << serverPort << "." << std::endl;
}

SocketServer::~SocketServer()
{
  std::cout << "Shutting down server..." << std::endl;
  close(_fd);
  std::cout << "Server shut down successfully." << std::endl;
}

Response*
SocketServer::onRequest(Request* req)
{
  std::cout << "Acknowledged request from client, size: " << req->size()
            << std::endl;
  delete req;
  return new Response();
}

Client&
SocketServer::clientByFileno(int fd)
{
  for (size_t i = 0; i < MAX_CLIENTS; i++) {
    if (_clients[i].fileno() == fd)
      return (_clients[i]);
  }
  throw SocketServer::ClientNotFound();
}

void
SocketServer::serve(void)
{
  SockAddrIn client;
  fd_set rfds;
  fd_set wfds;
  timeval tv;
  int cfd;

  tv.tv_sec = 0;
  tv.tv_usec = (long)(POLL_INTERVAL * 100000);
  int fdmax;
  socklen_t slen = sizeof(client);

  while (!_mustStop) {
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    FD_SET(_fd, &rfds);
    fdmax = _fd;

    for (int i = 0; i < MAX_CLIENTS; ++i) {
      Client& c = _clients[i];

      if (c.fileno() >= 0) {
        FD_SET(c.fileno(), &rfds);
        if (c.outsz() > 0)
          FD_SET(c.fileno(), &wfds);
        if (c.fileno() > fdmax)
          fdmax = c.fileno();
      }
    }

    int sel = select(fdmax + 1, &rfds, &wfds, 0, &tv);
    if (sel < 0 && errno != EINTR) {
      perror("SocketServer::serve - select");
      return;
    }

    if (FD_ISSET(_fd, &rfds)) {
      cfd = accept(_fd, (struct sockaddr*)&client, &slen);
      if (cfd < 0) {
        perror("SocketServer::serve - accept");
        return;
      }
      std::cerr << "[+][SocketServer] New client connected on fd " << cfd
                << std::endl;
      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (_clients[i].fileno() == -1) {
          _clients[i].setfileno(cfd);
          _clients[i].setoutsz(0);
          break;
        }
      }
    }

    for (int i = 0; i < MAX_CLIENTS; ++i) {
      Client& c = _clients[i];
      // int clientFd = c.fileno();
      if (c.fileno() > -1 && FD_ISSET(c.fileno(), &rfds)) {
        std::cerr << "[+][SocketServer] Received data from client #"
                  << c.fileno() - _fd << std::endl;
        Request* req = c.receive();
        if (!req) {
          onClientDisconnect(c);
          c.reset();
          continue;
        }
        Response* res = onRequest(req);
        c.setRes(res);
        // Nahla's notes : ici je peine a comprendre pourquoi separer en deux struct differentes et faire la lecture dans un autre if que celui de la l'ecriture
        // Si il n'y a pas de request, alors pas de response. On pourrais se dire "oui mais si le fd n'est pas en lecture a ce moment mais qu'il le deviens entre les deux"
        // Premierement : Dans quel cas ca pourrais arriver ? Deuxiemement : Dans ce cas, si une deuxieme requete etaisintercepter pendant ce laps de temps. onperdrais la premiere non ?
        // on pourais simplement faire un "onRequest" sur une string ? ou biens si on a peur de ne pas pouvoir ecrire il faudrais creer un array pour pouvoir ecrire toutes les reponses en attentes a la suite.
      }
      if (c.fileno() > -1 && FD_ISSET(c.fileno(), &wfds)) {
        if (c.respond() == 0) {
          onClientDisconnect(c);
          c.reset();
        }
      }
    }
  }
}

void
SocketServer::onClientDisconnect(Client& c)
{
  std::cout << "[*][SocketServer] Client on fd #" << c.fileno()
            << " disconnected." << std::endl;
}

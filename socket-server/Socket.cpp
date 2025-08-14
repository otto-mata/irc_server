#include "Socket.hpp"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>

SocketServer::SocketServer(unsigned short serverPort)
{
  port = htons(serverPort);
  fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (fd < 0)
    throw std::exception();
  int optValue = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(optValue)) <
      0) {
    perror("SocketServer::init - setsockopt");
    close(fd);
    throw std::exception();
  }
  ::memset(&in, 0, sizeof(in));
  ::memset(&clients, 0, sizeof(clients));
  in.sin_addr.s_addr = INADDR_ANY;
  in.sin_port = port;
  in.sin_family = AF_INET;
  if (bind(fd, (struct sockaddr*)&in, sizeof(in)) < 0) {
    perror("SocketServer::init - bind");
    close(fd);
    throw std::exception();
  }
  if (listen(fd, BACKLOG) < 0) {
    perror("SocketServer::init - listen");
    close(fd);
    throw std::exception();
  }
  mustStop = false;
  std::cout << "Server started on port " << serverPort << "." << std::endl;
}

SocketServer::~SocketServer()
{
  std::cout << "Shutting down server..." << std::endl;
  close(fd);
  std::cout << "Server shut down successfully." << std::endl;
}

Response*
SocketServer::onRequest(Request* req)
{
  std::cout << "Acknowledged request from client, size: " << req->size() << std::endl;
  return new Response();
}

Client&
SocketServer::clientByFileno(int fd)
{
  for (size_t i = 0; i < MAX_CLIENTS; i++)
  {
    if (clients[i].fileno() == fd)
      return (clients[i]);
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

  while (!mustStop) {
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    FD_SET(fd, &rfds);
    fdmax = fd;

    for (int i = 0; i < MAX_CLIENTS; ++i) {
      Client& c = clients[i];

      if (c.fileno() > 0) {
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

    if (FD_ISSET(fd, &rfds)) {
      cfd = accept(fd, (struct sockaddr*)&client, &slen);
      if (cfd < 0) {
        perror("SocketServer::serve - accept");
        return;
      }
      std::cerr << "[+][SocketServer] New client connected on fd " << cfd << std::endl;
      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].fileno() == -1) {
          clients[i].setfileno(cfd);
          clients[i].setoutsz(0);
          break;
        }
      }
    }

    for (int i = 0; i < MAX_CLIENTS; ++i) {
      Client& c = clients[i];
      if (c.fileno() > 0 && FD_ISSET(c.fileno(), &rfds)) {
        std::cerr << "[+][SocketServer] Received data from client #" << c.fileno() << std::endl;
        Request* req = c.receive();
        Response* res = onRequest(req);
        c.setRes(res);
      }
      if (c.fileno() > 0 && FD_ISSET(c.fileno(), &wfds)) {
        std::cerr << "[+][SocketServer] Sending data to client #" << c.fileno() << std::endl;
        c.respond();
      }
    }
  }
}

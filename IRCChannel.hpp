#ifndef IRCCHANNEL_HPP
#define IRCCHANNEL_HPP

#include "IRCClient.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>

class IRCChannel
{
private:
  std::string _name;
  std::set<IRCClient*> _users;
  IRCClient* _owner;
  std::string _password;
  size_t _maxUsers;
  bool _inviteOnly;
  bool _protectedTopic;
  std::string _topic;
  bool _botChannelActive;
  std::set<IRCClient*> _admins;
  std::set<IRCClient*> _guests;

public:
  IRCChannel();
  IRCChannel(std::string channel_name);
  IRCChannel(const IRCChannel& other);
  IRCChannel& operator=(const IRCChannel& other);
  ~IRCChannel();
  std::string getTopic() const;
  size_t getMaxUsers() const;
  IRCClient getOwner() const;
  std::set<IRCClient*> getGuests() const;
  std::string getPassword() const;
  bool isUserInChannel(IRCClient* user) const;
  bool isInviteOnly() const;
  bool isProtectedTopic() const;

  std::string getName();
  std::set<IRCClient*> getUserList();
  IRCClient* getUser(std::string user_name);

  std::set<IRCClient*> getAdminList();
  IRCClient* getAdmin(std::string admin_name);

  bool isUser(IRCClient* user_tofind);
  bool isUser(int user_tofind);
  bool isUser(std::string user_tofind);

  bool isAdmin(IRCClient* admin_tofind);
  bool isAdmin(int admin_tofind);
  bool isAdmin(std::string admin_tofind);

  void addUser(IRCClient* user_toadd);
  void removeUser(IRCClient* user_toremove);

  void adminUser(IRCClient* admin_toadd);
  void removeadminUser(IRCClient* admin_toremove);
};

#endif

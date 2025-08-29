#include "IRCChannel.hpp"

IRCChannel::IRCChannel()
  : _name("unnamed_channel")
{
}

IRCChannel::IRCChannel(std::string channel_name)
  : _name(channel_name)
{
}

IRCChannel::IRCChannel(const IRCChannel& other)
{
  *this = other;
}

IRCChannel&
IRCChannel::operator=(const IRCChannel& other)
{
  if (this != &other) {
    this->_name = other._name;
    this->_users = other._users;
  }
  return *this;
}

IRCChannel::~IRCChannel() {}

std::string
IRCChannel::getTopic() const
{
  return _topic;
}

size_t
IRCChannel::getMaxUsers() const
{
  return _maxUsers;
}

IRCClient
IRCChannel::getOwner() const
{
  return *_owner;
}

std::set<IRCClient*>
IRCChannel::getGuests() const
{
  return _guests;
}

std::string
IRCChannel::getPassword() const
{
  return _password;
}

bool
IRCChannel::isUserInChannel(IRCClient* user) const
{
  return _users.find(user) != _users.end();
}

bool
IRCChannel::isInviteOnly() const
{
  return _inviteOnly;
}

bool
IRCChannel::isProtectedTopic() const
{
  return _protectedTopic;
}

std::string
IRCChannel::getName()
{
  return _name;
}

std::set<IRCClient*>
IRCChannel::getUserList()
{
  return _users;
}

IRCClient*
IRCChannel::getUser(std::string user_name)
{
  // return user with name
}

std::set<IRCClient*>
IRCChannel::getAdminList()
{
  return _admins;
}

IRCClient*
getAdmin(std::string admin_name)
{
  // return admin with name
}

bool
IRCChannel::isUser(IRCClient* user_tofind)
{
  return _users.find(user_tofind) != _users.end();
}

bool
IRCChannel::isUser(int user_tofind)
{
  // check with id
}

bool
IRCChannel::isUser(std::string user_tofind)
{
  // check with name
}

bool
IRCChannel::isAdmin(IRCClient* admin_tofind)
{
  return _admins.find(admin_tofind) != _admins.end();
}

bool
IRCChannel::isAdmin(int admin_tofind)
{
  // check with id
}

bool
IRCChannel::isAdmin(std::string admin_tofind)
{
  // check with name
}

void
IRCChannel::addUser(IRCClient* user_toadd)
{
  if (!isUser(user_toadd)) {
    _users.insert(user_toadd);
  }
}

void
IRCChannel::removeUser(IRCClient* user_toremove)
{
  if (isAdmin(user_toremove)) {
    _admins.erase(user_toremove);
  }
  if (isUser(user_toremove)) {
    _users.erase(user_toremove);
  }
}

void
IRCChannel::adminUser(IRCClient* admin_toadd)
{
  if (isUser(admin_toadd) && !isAdmin(admin_toadd)) {
    _admins.insert(admin_toadd);
  }
}

void
IRCChannel::removeadminUser(IRCClient* admin_toremove)
{
  if (isAdmin(admin_toremove)) {
    _admins.erase(admin_toremove);
  }
}

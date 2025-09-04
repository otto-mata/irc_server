#include "IRCChannel.hpp"

IRCChannel::IRCChannel() : _name(DEFAULT_NAME), _topic(DEFAULT_TOPIC),
_userLimitCount(DEFAULT_USER_LIMIT_COUNT), _inviteOnly(DEFAULT_INVITE_ONLY),
_topicModifiable(DEFAULT__TOPIC_MODIFIABLE), _userLimit(DEFAULT__USER_LIMIT){}

IRCChannel::IRCChannel(std::string channel_name)  : _name(channel_name), _topic(DEFAULT_TOPIC),
_userLimitCount(DEFAULT_USER_LIMIT_COUNT), _inviteOnly(DEFAULT_INVITE_ONLY),
_topicModifiable(DEFAULT__TOPIC_MODIFIABLE), _userLimit(DEFAULT__USER_LIMIT) {}

IRCChannel::IRCChannel(const IRCChannel& other) {*this = other;}

IRCChannel& IRCChannel::operator=(const IRCChannel& other)
{
	if (this != &other)
	{
		this->_name = other._name + "_copy";
		//verifier si le nom existe deja
		this->_users = other._users;
		this->_admins = other._admins;
		this->_topic = other._topic;
		this->_userLimitCount = other._userLimitCount;
		this->_inviteOnly = other._inviteOnly;
		this->_topicModifiable = other._topicModifiable;
		this->_userLimit = other._userLimit;
	}
	return *this;
}

IRCChannel::~IRCChannel() {}

std::string IRCChannel::getName()
{
	return _name;
}

std::set<IRCClient*> IRCChannel::getUserList()
{
	return _users;
}

IRCClient* IRCChannel::getUser(std::string user_name)
{
	(void)user_name;
	return NULL;
}

std::set<IRCClient*> IRCChannel::getAdminList()
{
	return _admins;
}

IRCClient* getAdmin(std::string admin_name)
{
	(void)admin_name;
	return NULL;
}

std::string IRCChannel::getTopic()
{
	return _topic;
}

int IRCChannel::getUserLimitCount()
{
	return _userLimitCount;
}

bool IRCChannel::getInviteOnly()
{
	return _inviteOnly;
}

bool IRCChannel::getTopicModifiable()
{
	return _topicModifiable;
}

bool IRCChannel::getUserLimit()
{
	return _userLimit;
}

void IRCChannel::setTopic(std::string NewTopic)
{
	_topic = NewTopic;
}

void IRCChannel::setUserLimitCount(int NewUserLimit)
{
	_userLimit = NewUserLimit;
}

void IRCChannel::setInviteOnly(bool info)
{
	_inviteOnly = info;
}

void IRCChannel::setTopicModifiable(bool info)
{
	_topicModifiable = info;
}

void IRCChannel::setUserLimit(bool info)
{
	_userLimit = info;
}


bool IRCChannel::isUser(IRCClient* user_tofind)
{
	return _users.find(user_tofind) != _users.end();
}

bool IRCChannel::isUser(int user_tofind)
{
	(void)user_tofind;
	return false;
}

bool IRCChannel::isUser(std::string user_tofind)
{
	(void)user_tofind;
	return false;
}

bool IRCChannel::isAdmin(IRCClient* admin_tofind)
{
	return _admins.find(admin_tofind) != _admins.end();
}

bool IRCChannel::isAdmin(int admin_tofind)
{
	(void)admin_tofind;
	return false;
}

bool IRCChannel::isAdmin(std::string admin_tofind)
{
	(void)admin_tofind;
	return false;
}

void IRCChannel::addUser(IRCClient* user_toadd)
{
	if (!isUser(user_toadd))
	{
		_users.insert(user_toadd);
	}
}

void IRCChannel::removeUser(IRCClient* user_toremove)
{
	if (isAdmin(user_toremove))
	{
		_admins.erase(user_toremove);
	}
	if (isUser(user_toremove))
	{
		_users.erase(user_toremove);
	}
}

void IRCChannel::adminUser(IRCClient* admin_toadd)
{
	if (isUser(admin_toadd) && !isAdmin(admin_toadd))
	{
		_admins.insert(admin_toadd);
	}
}

void IRCChannel::removeadminUser(IRCClient* admin_toremove)
{
	if (isAdmin(admin_toremove))
	{
		_admins.erase(admin_toremove);
	}
}

void addUserWhitelist(IRCClient* admin_toadd)
{

}

void removeUserWhitelist(IRCClient* admin_toremove)
{
	
}

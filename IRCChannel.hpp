#ifndef IRCCHANNEL_HPP
# define IRCCHANNEL_HPP

#include "IRCClient.hpp"
# include <iostream>
# include <string>
# include <map>
# include <set>

#define DEFAULT_NAME "unamed_channel"
#define DEFAULT_TOPIC "undefined_topic"
#define DEFAULT_USER_LIMIT_COUNT 42
#define DEFAULT_INVITE_ONLY 0
#define DEFAULT__TOPIC_MODIFIABLE 1
#define DEFAULT__USER_LIMIT 0

class IRCChannel
{
	private:
		std::string _name;
		std::set<IRCClient*> _users;
		std::set<IRCClient*> _whitelist;
		std::set<IRCClient*> _admins;
		std::string _topic;
		int _userLimitCount;
		bool _inviteOnly;
		bool _topicModifiable;
		bool _userLimit;

	public:
		IRCChannel();
		IRCChannel(std::string channel_name);
		IRCChannel(const IRCChannel& other);
		IRCChannel& operator=(const IRCChannel& other);
		~IRCChannel();

		std::string getName();
		std::set<IRCClient*> getUserList();
		IRCClient* getUser(std::string user_name);

		std::set<IRCClient*> getAdminList();
		IRCClient* getAdmin(std::string admin_name);

		std::string getTopic();
		int getUserLimitCount();
		bool getInviteOnly();
		bool getTopicModifiable();
		bool getUserLimit();

		void setTopic(std::string NewTopic);
		void setUserLimitCount(int NewUserLimit);
		void setInviteOnly(bool info);
		void setTopicModifiable(bool info);
		void setUserLimit(bool info);

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

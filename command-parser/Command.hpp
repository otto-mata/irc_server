#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Token.hpp"
#include <vector>

class IRCServer;
class IRCChannel;

class Command
{
	private:
		IRCServer *_server;
		std::string _source;
		std::string _cmd;
		std::vector<std::string> _params;
		std::string _trailing;
		IRCChannel *_channel;
	public:
		Command();
		Command(IRCServer *serv);
		~Command();

		std::string getSource();
		std::string getCommand();
		std::vector<std::string> getParams();
		std::string getTrailing();

		void parse(std::string text);

		void execute();

		void executeKick();
		void executeMode();
		void executeInvite();
		void executeTopic();
};

#endif

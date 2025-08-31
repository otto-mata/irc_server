#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Token.hpp"
#include <vector>

class Command
{
	private:
		std::string _source;
		std::string _cmd;
		std::vector<std::string> _params;
		std::string _trailing;
	public:
		Command(std::vector<Token>& tv);
		~Command();
		void executeCmd(void);

		std::string getSource();
		std::string getCommand();
		std::vector<std::string> getParams();
		std::string getTrailing();
};

#endif

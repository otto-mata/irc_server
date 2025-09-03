#include "Command.hpp"
#include "Scanner.hpp"
#include "../IRCServer.hpp"

Command::Command() : _server(NULL) {}

Command::Command(IRCServer *serv) : _server(serv) {}

void Command::parse(std::string text)
{
	size_t i = 0;
	Scanner s(text);
	std::vector<Token> tv = s.scanTokens();
	_cmd = "";
	_source = "";
	_trailing = "";
	_params.clear();

	std::vector<Token>::iterator it = tv.begin();
	while (it != tv.end())
	{
		if (it->getType() == SPACE) {
			++it;
			continue;
		}

		// Source
		if (i == 0 && it->getType() == COLON)
		{
			++it;
			if (it != tv.end())
				_source = it->getLexeme();
		}
		// Commande
		else if ((i == 0 || i == 1) && it->getType() == STRING && _cmd.length() == 0)
		{
			_cmd = it->getLexeme();
		}
		// Trailing
		else if (it->getType() == COLON)
		{
			++it;
			while (it != tv.end())
			{
				if (it->getType() == STRING)
					_trailing += it->getLexeme();
				else if (it->getType() == SPACE)
					_trailing += " ";
				++it;
			}
			break;
		}
		// Params
		else if (it->getType() != EOL)
		{
			if (it->getType() == STRING)
				_params.push_back(it->getLexeme());
		}

		++it;
		++i;
	}
}

Command::~Command() {}

std::string Command::getSource()
{
	return _source;
}

std::string Command::getCommand()
{
	return _cmd;
}

std::vector<std::string> Command::getParams()
{
	return _params;
}

std::string Command::getTrailing()
{
	return _trailing;
}

void Command::execute()
{
	if (this->_cmd == "MSG")
	{
		// exec MSG
		return ;
	}
	if (_params.size() > 0 && _server->doesChannelExist(_params[0]) == false)
	{
		// channel not found
		return ;
	}
	if (this->_cmd == "KICK")
	{
		this->executeKick();
		return ;
	}
	if (this->_cmd == "INVITE")
	{
		this->executeInvite();
		return ;
	}
	if (this->_cmd == "TOPIC")
	{
		this->executeTopic();
		return ;
	}
	if (this->_cmd == "MODE")
	{
		this->executeMode();
		return ;
	}
	// error msg command not found
}

void Command::executeKick()
{

}

void Command::executeInvite()
{

}

void Command::executeTopic()
{

}

void Command::executeMode()
{

}

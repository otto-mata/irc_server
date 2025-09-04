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
		std::cout << "Channel not found" << std::endl;
		// channel not found
		return ;
	}
	_channel = _server->getChannel(_params[0]);
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
	std::cout << "Invalid Command" << std::endl;
	// error msg command not found
}

void Command::executeKick()
{
	if (_channel->isAdmin(_source) == false)
	{
		std::cout << "Kick command requires admin" << std::endl;
		//error message user isnt admin
	}
	if (_channel->isUserWhitelist(_params[2]))
	{
		
	}
	
}

void Command::executeInvite()
{

}

void Command::executeTopic()
{
	if (_params.size() > 1)
	{
		if (_channel->getTopicModifiable() == false
		&& _channel->isAdmin(_source) == false)
		{
			std::cout << "Channel isnt modifyable and user isnt admin" << std::endl;
			//error message can't modify topic
		}
		std::string res = _params[1];
		for (int i = 2; i < _params.size(); i++)
		{
			res = res + " " + _params[i];
		}
		_channel->setTopic(res);
	}
	else
	{
		std::cout << _channel->getTopic() << std::endl;
		//display topic
	}
}

void Command::executeMode()
{

}

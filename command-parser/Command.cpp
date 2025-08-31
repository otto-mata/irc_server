#include "Command.hpp"

Command::Command(std::vector<Token>& tv)
{
	size_t i = 0;

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

std::string Command::getSource()
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

void Command::executeCmd(void)
{

}

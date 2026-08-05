#include "../headers/CommandHandler.hpp"
#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include <cctype>

std::string CommandHandler::toUpper(const std::string& value)
{
	std::string result = value;

	for (size_t i = 0; i < result.size(); ++i)
	{
		result[i] = static_cast<char>(
			std::toupper(static_cast<unsigned char>(result[i]))
		);
	}

	return result;
}

e_command_type CommandHandler::getCommandType(const IRCMessage& message)
{
	std::string command;

	if (message.command.empty())
		return CMD_EMPTY;

	command = toUpper(message.command);

	if (command == "PASS")
		return CMD_PASS;
	if (command == "NICK")
		return CMD_NICK;
	if (command == "USER")
		return CMD_USER;
	if (command == "JOIN")
		return CMD_JOIN;
	if (command == "PRIVMSG")
		return CMD_PRIVMSG;
	if (command == "KICK")
		return CMD_KICK;
	if (command == "INVITE")
		return CMD_INVITE;
	if (command == "TOPIC")
		return CMD_TOPIC;
	if (command == "MODE")
		return CMD_MODE;
	if (command == "CAP")
		return CMD_CAP;
	if (command == "PING")
		return CMD_PING;
	if (command == "QUIT")
		return CMD_QUIT;

	return CMD_UNKNOWN;
}

const char* CommandHandler::getCommandName(e_command_type type)
{
	if (type == CMD_EMPTY)
		return "EMPTY";
	if (type == CMD_PASS)
		return "PASS";
	if (type == CMD_NICK)
		return "NICK";
	if (type == CMD_USER)
		return "USER";
	if (type == CMD_JOIN)
		return "JOIN";
	if (type == CMD_PRIVMSG)
		return "PRIVMSG";
	if (type == CMD_KICK)
		return "KICK";
	if (type == CMD_INVITE)
		return "INVITE";
	if (type == CMD_TOPIC)
		return "TOPIC";
	if (type == CMD_MODE)
		return "MODE";
	if (type == CMD_CAP)
		return "CAP";
	if (type == CMD_PING)
		return "PING";
	if (type == CMD_QUIT)
		return "QUIT";

	return "UNKNOWN";
}

void CommandHandler::execute(Server& server, Client& client,
	const IRCMessage& message)
{
	e_command_type type;

	type = getCommandType(message);

	if (type == CMD_EMPTY)
		return;

	if (type == CMD_PASS)
		handlePass(server, client, message);
	else if (type == CMD_NICK)
		handleNick(server, client, message);
	else if (type == CMD_USER)
		handleUser(server, client, message);
	else if (type == CMD_JOIN
		|| type == CMD_PRIVMSG
		|| type == CMD_KICK
		|| type == CMD_INVITE
		|| type == CMD_TOPIC
		|| type == CMD_MODE)
	{
		if (!client.is_registered())
		{
			sendNumeric(server, client, "451", "",
				"You have not registered");
		}
	}
	else if (type == CMD_UNKNOWN)
	{
		sendNumeric(server, client, "421", message.command,
			"Unknown command");
	}
}

void CommandHandler::sendNumeric(Server& server, const Client& client,
	const std::string& code,
	const std::string& middle,
	const std::string& trailing)
{
	std::string target;
	std::string reply;

	if (client.get_nickname().empty())
		target = "*";
	else
		target = client.get_nickname();

	reply = ":ircserv " + code + " " + target;

	if (!middle.empty())
		reply += " " + middle;

	reply += " :" + trailing + "\r\n";

	server.queue_message(client.get_fd(), reply);
}

void CommandHandler::handlePass(Server& server, Client& client,
	const IRCMessage& message)
{
	if (client.is_registered())
	{
		sendNumeric(server, client, "462", "",
			"You may not reregister");
		return;
	}

	if (message.params.empty())
	{
		sendNumeric(server, client, "461", "PASS",
			"Not enough parameters");
		return;
	}

	if (message.params[0] != server.get_password())
	{
		client.set_password_accepted(false);

		sendNumeric(server, client, "464", "",
			"Password incorrect");
		return;
	}

	client.set_password_accepted(true);
	tryRegister(server, client);
}

bool CommandHandler::isValidNickname(const std::string& nickname)
{
	size_t i;

	if (nickname.empty())
		return false;

	if (!std::isalpha(static_cast<unsigned char>(nickname[0]))
		&& nickname[0] != '['
		&& nickname[0] != ']'
		&& nickname[0] != '\\'
		&& nickname[0] != '`'
		&& nickname[0] != '^'
		&& nickname[0] != '{'
		&& nickname[0] != '}'
		&& nickname[0] != '|'
		&& nickname[0] != '_')
	{
		return false;
	}

	i = 1;
	while (i < nickname.size())
	{
		if (!std::isalnum(static_cast<unsigned char>(nickname[i]))
			&& nickname[i] != '-'
			&& nickname[i] != '['
			&& nickname[i] != ']'
			&& nickname[i] != '\\'
			&& nickname[i] != '`'
			&& nickname[i] != '^'
			&& nickname[i] != '{'
			&& nickname[i] != '}'
			&& nickname[i] != '|'
			&& nickname[i] != '_')
		{
			return false;
		}
		++i;
	}
	return true;
}

void CommandHandler::handleNick(Server& server, Client& client,
	const IRCMessage& message)
{
	std::string nickname;

	if (message.params.empty() || message.params[0].empty())
	{
		sendNumeric(server, client, "431", "",
			"No nickname given");
		return;
	}

	nickname = message.params[0];

	if (!isValidNickname(nickname))
	{
		sendNumeric(server, client, "432", nickname,
			"Erroneous nickname");
		return;
	}

	if (server.is_nick_taken(nickname, client.get_fd()))
	{
		sendNumeric(server, client, "433", nickname,
			"Nickname is already in use");
		return;
	}

	client.set_nickname(nickname);

	tryRegister(server, client);
}

void CommandHandler::handleUser(Server& server, Client& client,
	const IRCMessage& message)
{
	if (client.is_registered())
	{
		sendNumeric(server, client, "462", "",
			"You may not reregister");
		return;
	}

	if (message.params.size() < 4)
	{
		sendNumeric(server, client, "461", "USER",
			"Not enough parameters");
		return;
	}

	if (message.params[0].empty())
	{
		sendNumeric(server, client, "461", "USER",
			"Not enough parameters");
		return;
	}

	client.set_username(message.params[0]);
	client.set_realname(message.params[3]);

	tryRegister(server, client);
}

void CommandHandler::tryRegister(Server& server, Client& client)
{
	std::string welcome;

	if (client.is_registered())
		return;

	if (!client.is_password_accepted())
		return;

	if (!client.has_nickname())
		return;

	if (!client.has_username())
		return;

	client.set_registered(true);

	welcome = ":ircserv 001 " + client.get_nickname()
		+ " :Welcome to the ft_irc network "
		+ client.get_nickname()
		+ "!" + client.get_username()
		+ "@localhost\r\n";

	server.queue_message(client.get_fd(), welcome);
}
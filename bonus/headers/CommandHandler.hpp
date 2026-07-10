#pragma once
#include "Parser.hpp"
#include <string>

class Server;
class Client;

enum e_command_type
{
    CMD_EMPTY,
    CMD_PASS,
    CMD_NICK,
    CMD_USER,
    CMD_JOIN,
    CMD_PRIVMSG,
    CMD_KICK,
    CMD_INVITE,
    CMD_TOPIC,
    CMD_MODE,
    CMD_CAP,
    CMD_PING,
    CMD_QUIT,
    CMD_UNKNOWN
};

class CommandHandler
{
public:
    static e_command_type getCommandType(const IRCMessage& message);
    static const char* getCommandName(e_command_type type);

    static void execute(Server& server, Client& client,
        const IRCMessage& message);

private:
    static std::string toUpper(const std::string& value);

    static void handlePass(Server& server, Client& client,
        const IRCMessage& message);

    static void handleNick(Server& server, Client& client,
        const IRCMessage& message);

    static void handleUser(Server& server, Client& client,
        const IRCMessage& message);

    static void tryRegister(Server& server, Client& client);

    static void sendNumeric(Server& server, const Client& client,
        const std::string& code,
        const std::string& middle,
        const std::string& trailing);

    static bool isValidNickname(const std::string& nickname);
};
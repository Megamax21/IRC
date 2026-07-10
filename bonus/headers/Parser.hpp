#pragma once
#include <string>
#include <vector>

class Client;

struct IRCMessage
{
    std::string command;
    std::vector<std::string> params;
};

class Parser
{
public:
    static bool hasCompleteCommand(Client& client);
    static std::string extractCommand(Client& client);
    static IRCMessage parseLine(const std::string& line);
};
#include "../headers/Parser.hpp"
#include <sstream>

/*bool Parser::hasCompleteCommand(Client& client)
{
    return client.getBuffer().find("\n") != std::string::npos;
}

std::string Parser::extractCommand(Client& client)
{
    std::string& buffer = client.getBuffer();

    size_t pos = buffer.find("\n");

    std::string command = buffer.substr(0, pos);

    buffer.erase(0, pos + 1);

    if (!command.empty() && command[command.size() - 1] == '\r')
        command.erase(command.size() - 1);

    return command;
}*/

IRCMessage Parser::parseLine(const std::string& line)
{
    IRCMessage msg;
    std::istringstream iss(line);
    std::string token;

    if (!(iss >> msg.command))
        return msg;

    while (iss >> token)
    {
        if (!token.empty() && token[0] == ':')
        {
            std::string trailing = token.substr(1);
            std::string rest;

            std::getline(iss, rest);

            if (!rest.empty())
                trailing += rest;

            msg.params.push_back(trailing);
            break;
        }
        else
        {
            msg.params.push_back(token);
        }
    }

    return msg;
}
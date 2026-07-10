#include "../headers/Parser.hpp"
#include "../headers/Client.hpp"
#include <sstream>

bool Parser::hasCompleteCommand(Client& client)
{
    return client.get_input_buffer().find('\n') != std::string::npos;
}

std::string Parser::extractCommand(Client& client)
{
    std::string& buffer = client.get_input_buffer();
    size_t pos = buffer.find('\n');

    std::string line = buffer.substr(0, pos);

    buffer.erase(0, pos + 1);

    if (!line.empty() && line[line.size() - 1] == '\r')
        line.erase(line.size() - 1);

    return line;
}

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
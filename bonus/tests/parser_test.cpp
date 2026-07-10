#include "../headers/Parser.hpp"
#include "../headers/CommandHandler.hpp"
#include <iostream>

static void testDispatcher(const std::string& line)
{
    IRCMessage message = Parser::parseLine(line);
    e_command_type type = CommandHandler::getCommandType(message);

    std::cout << "Line: [" << line << "]" << std::endl;
    std::cout << "Command parsed: [" << message.command << "]" << std::endl;
    std::cout << "Dispatcher result: ["
              << CommandHandler::getCommandName(type)
              << "]" << std::endl;
    std::cout << "------------------------" << std::endl;
}

int main()
{
    testDispatcher("PASS 1234");
    testDispatcher("NICK tom");
    testDispatcher("USER tom 0 * :Tom Anton");
    testDispatcher("JOIN #42");
    testDispatcher("PRIVMSG #42 :bonjour");
    testDispatcher("MODE #42 +i");
    testDispatcher("ping serveur");
    testDispatcher("CAP LS 302");
    testDispatcher("COMMAND_INCONNUE test");
    testDispatcher("");

    return 0;
}
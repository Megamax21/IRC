/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 22:47:03 by sbehar            #+#    #+#             */
/*   Updated: 2026/08/24 22:47:03 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Parser.hpp"
#include <string>
#include <vector>
#include <sstream>

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

e_command_type getCommandType(const IRCMessage& message);
const char* getCommandName(e_command_type type);

void execute(Server& server, Client& client, const IRCMessage& message);
void tryRegister(Server& server, Client& client);
void sendNumeric(Server& server, const Client& client,
        const std::string& code,
        const std::string& middle,
        const std::string& trailing);

bool isValidNickname(const std::string& nickname);
bool isValidChannelName(const std::string &name);

std::string toUpper(const std::string& value);
std::vector<std::string> split(const std::string &value, char delimiter);

void handlePass(Server& server, Client& client, const IRCMessage& message);
void handleNick(Server& server, Client& client, const IRCMessage& message);
void handleUser(Server& server, Client& client, const IRCMessage& message);
void handleCap(Server& server, Client& client, const IRCMessage& message);
void handlePing(Server& server, Client& client, const IRCMessage& message);
void executeJoin(Server &server, Client &client, const IRCMessage &message);
void executePrivMsg(Server &server, Client &client, const IRCMessage &message);
void executeKick(Server &server, Client &client, const IRCMessage &message);
void executeInvite(Server &server, Client &client, const IRCMessage &message);
void executeTopic(Server &server, Client &client, const IRCMessage &message);

void leaveAllChannels(Server &server, Client &client);
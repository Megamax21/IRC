/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:27:28 by sbehar            #+#    #+#             */
/*   Updated: 2026/07/06 22:27:28 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
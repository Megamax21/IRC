/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 18:34:41 by sbehar            #+#    #+#             */
/*   Updated: 2026/11/02 18:34:41 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

bool    isValidNickname(const std::string& nickname)
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

void    handleNick(Server& server, Client& client,
	const IRCMessage& message)
{
	if (message.params.empty() || message.params[0].empty())
	{
		sendNumeric(server, client, "431", "", "No nickname given");
		return;
	}

	std::string nickname = message.params[0];

	if (!isValidNickname(nickname))
	{
		sendNumeric(server, client, "432", nickname, "Erroneous nickname");
		return;
	}

	if (server.isNicknameTaken(nickname, client.getFd()))
	{
		sendNumeric(server, client, "433", nickname,
			"Nickname is already in use");
		return;
	}

	const bool			wasRegistered = client.isRegistered();

	if (wasRegistered && client.getNickname() == nickname)
		return;
	
	const std::string	oldPrefix = client.getPrefix();

	client.setNickname(nickname);

	if (wasRegistered)
	{
		const std::string	reply = oldPrefix + " NICK :" + nickname + "\r\n";
		server.broadcastToSharedChannels(client, reply);
	}
	else
		tryRegister(server, client);
}

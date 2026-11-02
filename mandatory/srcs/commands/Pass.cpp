/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 18:38:37 by sbehar            #+#    #+#             */
/*   Updated: 2026/11/02 18:38:37 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

void    handlePass(Server& server, Client& client,
	const IRCMessage& message)
{
	if (client.isRegistered())
	{
		sendNumeric(server, client, "462", "", "You may not reregister");
		return;
	}

	if (message.params.empty())
	{
		sendNumeric(server, client, "461", "PASS", "Not enough parameters");
		return;
	}

	if (message.params[0] != server.getPassword())
	{
		client.setPasswordAccepted(false);
		sendNumeric(server, client, "464", "", "Password incorrect");
		return;
	}

	client.setPasswordAccepted(true);
	tryRegister(server, client);
}
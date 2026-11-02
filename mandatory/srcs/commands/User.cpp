/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 18:40:32 by sbehar            #+#    #+#             */
/*   Updated: 2026/11/02 18:40:32 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

void    handleUser(Server& server, Client& client,
	const IRCMessage& message)
{
	if (client.isRegistered())
	{
		sendNumeric(server, client, "462", "", "You may not reregister");
		return;
	}

	if (message.params.size() < 4)
	{
		sendNumeric(server, client, "461", "USER", "Not enough parameters");
		return;
	}

	client.setUsername(message.params[0]);
	std::cout << " under username => " << message.params[0] << std::endl;
	client.setRealname(message.params[3]);

	tryRegister(server, client);
}
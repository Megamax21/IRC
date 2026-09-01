/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 08:31:12 by sbehar            #+#    #+#             */
/*   Updated: 2026/09/01 08:31:12 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

void    executeInvite(Server &server, Client &client, const IRCMessage &message)
{
    // Invite nécessite deux paramètres
    if (message.params.size() < 2)
    {
        sendNumeric(server, client, "461", "INVITE", "Not enough parameters");
        return;
    }

    const std::string   &targetNick = message.params[0];
    const std::string   &channelName = message.params[1];

    Channel *channel = server.getChannel(channelName);

    if (!channel)
    {
        sendNumeric(server, client, "403", channelName, "No such channel");
        return;
    }
    // uniquement les opérateurs du channel peuvent inviter
    if (!channel->isOperator(&client))
    {
        sendNumeric(server, client, "482", channelName, "You're not a channel operator");
        return;
    }

    Client  *target = server.getClientByNickname(targetNick);

    if (!target)
    {
        sendNumeric(server, client, "401", targetNick, "No such nick");
        return;
    }
    if (channel->isMember(target))
    {
        sendNumeric(server, client, "443", channelName, "User is already on channel");
        return;
    }
    channel->addInvite(target);

    std::string inviteMessage = client.getPrefix() +
                                " INVITE " + targetNick +
                                " " + channelName + "\r\n";
    
    server.queueMessage(target->getFd(), inviteMessage);
    sendNumeric(server, client, "341", targetNick + " " + channelName, "");
}
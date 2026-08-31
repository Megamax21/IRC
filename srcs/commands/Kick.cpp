/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 01:10:28 by sbehar            #+#    #+#             */
/*   Updated: 2026/09/01 01:10:28 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

void    executeKick(Server &server, Client &client, const IRCMessage &message)
{
    // KICK nécessite au moins 2 paramètres
    if (message.params.size() < 2)
    {
        sendNumeric(server, client, "461", "KICK", "Not enough parameters");
        return;
    }

    const std::string   &channelName = message.params[0];
    const std::string   &targetNick = message.params[1];
          std::string   reason;
    
    if (message.params.size() >= 3)
        reason = message.params[2];
    
    Channel *channel = server.getChannel(channelName);

    if (!channel)
    {
        sendNumeric(server, client, "403", channelName, "No such channel");
        return;
    }
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
    if (!channel->isMember(target))
    {
        sendNumeric(server, client, "441", channelName, "They aren't on that channel");
        return;
    }

    std::string kickMessage = client.getPrefix() +
                              " KICK " + channelName
                              + " " + targetNick;
    
    if (!reason.empty())
        kickMessage += " :" + reason;
    kickMessage += "\r\n";
    server.sendToChannel(channel, kickMessage, NULL);
    channel->removeMember(target);
    if (channel->getMemberCount() == 0)
        server.deleteChannel(channelName);
}
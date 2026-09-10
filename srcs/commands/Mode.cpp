/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 06:07:12 by sbehar            #+#    #+#             */
/*   Updated: 2026/09/10 06:07:12 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

static std::string  buildModeReply(const Client &client, const Channel &channel)
{
    std::string modes = "+";

    if (channel.isInviteOnly())
        modes += "i";
    if (channel.isTopicRestricted())
        modes += "t";
    if (channel.hasKey())
        modes += "k";
    if (channel.hasLimit())
        modes += "l";
        
    std::string reply = ":ircserv 324 " + client.getNickname()
                        + " " + channel.getName() + " " + modes;
        
    if (channel.hasKey())
        reply += " " + channel.getKey();
    if (channel.hasLimit())
    {
        std::ostringstream  oss;

        oss << channel.getLimit();
        reply += " " + oss.str();
    }
    reply += "\r\n";
    return (reply);
}

void    executeMode(Server &server, Client &client, const IRCMessage &message)
{
    // MODE nécessite au moins un paramètre
    if (message.params.empty())
    {
        sendNumeric(server, client, "461", "MODE", "Not enough parameters");
        return;
    }

    const std::string   &channelName = message.params[0];
    Channel             *channel = server.getChannel(channelName);

    if (!channel)
    {
        sendNumeric(server, client, "403", channelName, "No such channel");
        return;
    }
    if (!channel->isMember(&client))
    {
        sendNumeric(server, client, "442", channelName, "You're not on that channel");
        return;
    }
    
    // 1er cas : aucun mode fourni -> on renvoie les modes actuels
    if (message.params.size() == 1)
    {
        std::string reply = buildModeReply(client, *channel);

        server.queueMessage(client.getFd(), reply);
        return;
    }

    // 2nd cas : modes fournis
    std::string modeStr = message.params[1];

    if (!channel->isOperator(&client))
    {
        sendNumeric(server, client, "482", channelName, "You're not a channel operator");
        return;
    }
    if (modeStr.size() < 2 || (modeStr[0] != '+' && modeStr[0] != '-'))
    {
        sendNumeric(server, client, "472", modeStr, "Unknown mode");
        return;
    }

    char        sign = modeStr[0];
    char        mode = modeStr[1];
    size_t      argIndex = 2;
    std::string modeNotification = client.getPrefix() + " MODE "
                                   + channelName + " " + sign + mode;
    std::string argStr;

    switch (mode)
    {
        case 'i':
            if (sign == '+')
                channel->setInviteOnly(true);
            else
                channel->setInviteOnly(false);
            break;

        case 't':
            if (sign == '+')
                channel->setTopicRestricted(true);
            else
                channel->setTopicRestricted(false);
            break;

        case 'k':
            if (argIndex >= message.params.size())
            {
                sendNumeric(server, client, "461", "MODE", "Not enough parameters");
                return;
            }
            argStr = message.params[argIndex];
            if (sign == '+')
            {
                channel->setKey(argStr);
                modeNotification += " " + argStr;
            }
            else
            {
                channel->removeKey();
                modeNotification += " " + argStr;
            }
            break;
        
        case 'o':
        {
            if (argIndex >= message.params.size())
            {
                sendNumeric(server, client, "461", "MODE", "Not enough parameters");
                return;
            }
            argStr = message.params[argIndex];

            Client  *target = server.getClientByNickname(argStr);

            if (!target)
            {
                sendNumeric(server, client, "401", argStr, "No such nick");
                return;
            }
            if (!channel->isMember(target))
            {
                sendNumeric(server, client, "441", channelName, "They aren't on that channel");
                return;
            }
            modeNotification += " " + argStr;
            if (sign == '+')
                channel->addOperator(target);
            else
                channel->removeOperator(target);
            break;
        }
        case 'l':
        {
            if (sign == '+')
            {
                if (argIndex >= message.params.size())
                {
                    sendNumeric(server, client, "461", "MODE", "Not enough parameters");
                    return;
                }
                argStr = message.params[argIndex];

                int limit = 0;

                for (size_t i = 0; i < argStr.size(); ++i)
                {
                    if (argStr[i] < '0' || argStr[i] > '9')
                    {
                        sendNumeric(server, client, "461", "MODE", "Invalid limit");
                        return;
                    }
                    limit = limit * 10 + (argStr[i] - '0');
                }
                if (limit <= 0)
                {
                    sendNumeric(server, client, "461", "MODE", "Invalid limit");
                    return;
                }
                channel->setLimit(static_cast<size_t>(limit));
                modeNotification += " " + argStr;
            }
            else
                channel->removeLimit();
            break;
        }
        default:
            sendNumeric(server, client, "472", std::string(1, mode), "Unknown mode");
            return;
    }
    modeNotification += "\r\n";
    server.sendToChannel(channel, modeNotification, NULL);

    std::string reply = buildModeReply(client, *channel);

    server.queueMessage(client.getFd(), reply);
}
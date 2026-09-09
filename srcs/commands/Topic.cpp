/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 07:36:49 by sbehar            #+#    #+#             */
/*   Updated: 2026/09/09 07:36:49 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

void    executeTopic(Server &server, Client &client, const IRCMessage &message)
{
    // TOPIC nécessite au moins un paramètre
    if (message.params.empty())
    {
        sendNumeric(server, client, "461", "TOPIC", "Not enough parameters");
        return;
    }

    const std::string   &channelName = message.params[0];

    Channel *channel = server.getChannel(channelName);

    if (!channel)
    {
        sendNumeric(server, client, "403", channelName, "No such channel");
        return;
    }
    // Le client doit être membre du channel
    if (!channel->isMember(&client))
    {
        sendNumeric(server, client, "442", channelName, "You're not on that channel");
        return;
    }
    // 1er cas : aucun topic fourni -> on renvoie le topic actuel
    if (message.params.size() == 1)
    {
        if (channel->getTopic().empty())
            sendNumeric(server, client, "331", channelName, "No topic is set");
        else
            sendNumeric(server, client, "332", channelName, channel->getTopic());
        return;
    }
    // 2nd cas : un topic est fourni -> si le paramètre est vide on retire le topic
    
    std::string newTopic = message.params[1];

    // si l'user mets ":" en topic, on retire le topic
    if (newTopic == ":")
        newTopic.clear();
    // si le channel est en mode +t, seuls les opérateurs peuvent changer le topic
    if (channel->isTopicRestricted() && !channel->isOperator(&client))
    {
        sendNumeric(server, client, "462", channelName, "You're not a channel operator");
        return;
    }
    channel->setTopic(newTopic);

    std::string topicMsg = client.getPrefix() + " TOPIC " + channelName;

    if (!newTopic.empty())
        topicMsg += " :" + newTopic;
    topicMsg += "\r\n";
    server.sendToChannel(channel, topicMsg, NULL);
    if (!newTopic.empty())
        sendNumeric(server, client, "332", channelName, newTopic);
    else
        sendNumeric(server, client, "331", channelName, "No topic is set");
}
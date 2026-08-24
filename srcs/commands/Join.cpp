/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 22:46:24 by sbehar            #+#    #+#             */
/*   Updated: 2026/08/24 22:46:24 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

void    sendJoinError(Client &client, int num, const std::string &channelName, const std::string &reason)
{
    std::ostringstream  oss;

    oss << ":ircserv ";
    oss << num << " ";
    oss << client.get_nickname() << " ";
    if (!channelName.empty())
        oss << channelName << " ";
    oss << ":" << reason << "\r\n";
    client.append_output(oss.str());
}

void    sendJoinMessage(Server &server, Channel &channel, Client &client)
{
    std::string message = client.get_prefix() + " JOIN :" + channel.getName() + "\r\n";
    server.broadcastToChannel(&channel, message);
}

void    sendJoinTopic(Channel &channel, Client &client)
{
    if (channel.getTopic().empty())
        return ;
    client.append_output(":ircserv 332 " + client.get_nickname() + " " +
        channel.getName() + " :" + channel.getTopic() + "\r\n");
}

void    sendJoinNames(Channel &channel, Client &client)
{
    std::string                 names;
    const std::vector<Client*>  &members = channel.getMembers();

    for (std::vector<Client*>::const_iterator it = members.begin();
        it != members.end(); ++it)
    {
        if (!*it)
            continue;
        if (!names.empty())
            names += " ";
        if (channel.isOperator(*it))
            names += "@";
        names += (*it)->get_nickname();
    }
    client.append_output(":ircserv 353 " + client.get_nickname()
        + " = " + channel.getName() + " :" + names + "\r\n");
    client.append_output(":ircserv 366 " + client.get_nickname()
        + " " + channel.getName() + " :End of /NAMES list.\r\n");
}

void    executeJoin(Server &server, Client &client, const IRCMessage &message)
{
    // si pas de paramètres -> erreur 461
    if (message.params.empty())
    {
        client.append_output(":ircserv 461 " + client.get_nickname()
            + "JOIN :Not enough parameters\r\n");
        return ;
    }
    // gère le cas de JOIN 0 (le client quitte tout ses channels actuels)
    if (message.params[0] == "0")
    {
        leaveAllChannels(server, client);
        return ;
    }

    // le premier paramètre contient un ou plusieurs noms de channels
    std::vector<std::string>    channelNames = split(message.params[0], ',');

    // le second contient éventuellement les keys
    std::vector<std::string>    keys;

    if (message.params.size() >= 2)
        keys = split(message.params[1], ',');

    // chaque channel est traîté independamment, une erreur sur #a 
    // n'empêche pas le traitement de #b

    for (size_t i = 0; i < channelNames.size(); ++i)
    {
        const std::string   &channelName = channelNames[i];

        if (!isValidChannelName(channelName))
        {
            sendJoinError(
                client,
                403,
                channelName,
                "No such channel");
            continue;
        }

        Channel *channel = server.getChannel(channelName);
        bool    channelCreated = false;

        // si le channel n'existe pas, on le crée
        // l'utilisateur qui crée le channel devient automatiquement opérateur
        if (!channel)
        {
            channel = server.createChannel(channelName);
            channelCreated = true;
        }

        // si le client est déjà membre, on ne l'ajoute pas deux fois
        if (channel->isMember(&client))
            continue;
        
        // on récupère la clé correspondant au canal
        std::string suppliedKey;

        if (i < keys.size())
            suppliedKey = keys[i];
        
        // vérification du mode +i
        if (!channelCreated && channel->isInviteOnly() &&
            !channel->isInvited(&client))
        {
            sendJoinError(
                client,
                473,
                channelName,
                "Cannot join channel (+i)");
            continue;
        }
        // vérification du mode +k
        if (!channelCreated && channel->hasKey() &&
            suppliedKey != channel->getKey())
        {
            sendJoinError(
                client,
                475,
                channelName,
                "Cannot join channel (+k)");
            continue;
        }
        // vérification du mode +l
        if (!channelCreated && channel->hasLimit() &&
            channel->getMemberCount() >= channel->getLimit())
        {
            sendJoinError(
                client,
                471,
                channelName,
                "Cannot join channel (+l)");
            continue;
        }
        channel->addMember(&client);
        if (channelCreated)
            channel->addOperator(&client);
        channel->removeInvite(&client);
        sendJoinMessage(
            server,
            *channel,
            client);
        sendJoinTopic(
            *channel,
            client);
        sendJoinNames(
            *channel,
            client);
    }
}
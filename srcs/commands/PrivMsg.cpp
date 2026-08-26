/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 21:05:23 by sbehar            #+#    #+#             */
/*   Updated: 2026/08/26 21:05:23 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"
#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Channel.hpp"

void    executePrivMsg(Server &server, Client &client, const IRCMessage &message)
{
    // PRIVMSG nécessite deux paramètres : PRIVMSG <target> :<message>
    if (message.params.size() < 2)
    {
        sendNumeric(server, client, "461", "PRIVMSG", "Not enough parameters");
        return;
    }
    
    const std::string   &target = message.params[0];
    const std::string   &text = message.params[1];

    if (target.empty() || text.empty())
    {
        sendNumeric(server, client, "412", "", "No text to send");
        return;
    }
    if (target[0] == '#' || target[0] == '&')
    {
        Channel *channel = server.getChannel(target);

        if (!channel)
        {
            sendNumeric(server, client, "403", target, "No such channel");
            return;
        }
        // Un client doit être membre du channel pour y envoyer un message
        if (!channel->isMember(&client))
        {
            sendNumeric(server, client, "404", target, "Cannot send to channel");
            return;
        }

        // Le message IRC doit contenir : :sender!user@host PRIVMSG #channel :text
        // Il nous faut juste envoyer le message aux autres membres
        std::string outgoing = client.getPrefix() +
                            " PRIVMSG " +
                            target + " :" + text + "\r\n";
        
        server.sendToChannel(channel, outgoing, &client);
        return;
    }
    // Si <target> ne commence ni par '#' ni par '&', on l'interprète comme un pseudo
    Client  *recipient = server.getClientByNickname(target);

    if (!recipient)
    {
        sendNumeric(server, client, "401", target, "No such nick");
        return;
    }

    std::string outgoing = client.getPrefix() +
                            " PRIVMSG " +
                            recipient->getNickname() +
                            " :" + text + "\r\n";
    
    server.queueMessage(recipient->getFd(), outgoing);
}
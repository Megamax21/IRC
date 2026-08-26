/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:44 by ml-hote           #+#    #+#             */
/*   Updated: 2026/08/26 22:11:46 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Parser.hpp"
#include "../../headers/Commands.hpp"

Server::Server() : _password("1234"), _socket(0), _port(0)
{
	std::cout << "Server constructor called" << std::endl;
}

Server::Server(int port, std::string password) : _password(password), _socket(0), _port(port)
{
	std::cout << "Server constructor called with args" << std::endl;
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

// On utilise std::map qui stocke des paires (std::pair<const Key, T>)
// dans notre cas : std::pair<channel_name, Channel>
// donc it->first est la clé, une string (channel_name)
// et it->second est la valeur (Channel)

Channel	*Server::getChannel(const std::string &name)
{
	std::map<std::string, Channel>::iterator it = _channels.find(name);
	if (it == _channels.end())
		return (NULL);
	return (&it->second);
}

// insert -> ajoute un nouvel élément (clé/valeur)
// et renvoie une paire (std::pair<iterator, bool>)
// avec un itérateur sur l'élément, soit celui inséré, soit un élement déjà existant
// & un booléen qui indique si l'insertion a réussi ou si la clé
// existait déjà
// make_pair -> crée une paire 

Channel	*Server::createChannel(const std::string &name)
{
	std::pair<std::map<std::string, Channel>::iterator, bool> res =
		_channels.insert(std::make_pair(name, Channel(name)));
	return (&res.first->second);
}

void	Server::removeClientFromAllChannels(Client *client)
{
	for (std::map<std::string, Channel>::iterator it = _channels.begin();
		it != _channels.end();
		++it)
	{
		Channel	&channel = it->second;

		if (!channel.isMember(client))
			continue;
		
		std::string	message = 
			client->getPrefix() +
			" PART " +
			channel.getName() +
			" : Leaving all channels\r\n";
		broadcastToChannel(&channel, message);
		channel.removeMember(client);
	}
}

void	Server::broadcastToChannel(Channel *channel, const std::string &message)
{
	if (!channel)
		return ;

	const std::vector<Client*>	&members = channel->getMembers();

	for (std::vector<Client*>::const_iterator it = members.begin();
		it != members.end(); ++it)
	{
		if (*it)
			queueMessage((*it)->getFd(), message);
	}
}

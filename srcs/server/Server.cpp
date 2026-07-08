/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:44 by ml-hote           #+#    #+#             */
/*   Updated: 2026/07/08 21:31:09 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/Server.hpp"

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

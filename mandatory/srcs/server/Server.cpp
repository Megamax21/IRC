/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:44 by ml-hote           #+#    #+#             */
/*   Updated: 2026/07/10 11:06:59 by ml-hote          ###   ########.fr       */
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

void Server::queue_message(int clientSocket, const std::string& message)
{
	send(clientSocket, message.c_str(), message.size(), 0);
}

bool Server::is_nick_taken(const std::string&, int)
{
	return false;
}
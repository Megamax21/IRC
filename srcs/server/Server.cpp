/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:44 by ml-hote           #+#    #+#             */
/*   Updated: 2026/06/19 04:22:25 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Parser.hpp"
#include "../../headers/CommandHandler.hpp"

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
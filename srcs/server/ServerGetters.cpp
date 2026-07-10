/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerGetters.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 03:29:40 by ml-hote           #+#    #+#             */
/*   Updated: 2026/07/06 16:48:48 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Parser.hpp"
#include "../../headers/CommandHandler.hpp"

std::string	Server::get_password() const
{
	return (this->_password);
}

int	Server::get_port() const
{
	return (this->_port);
}

int	Server::get_socket() const
{
	return (this->_socket);
}
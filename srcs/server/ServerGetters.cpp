/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerGetters.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 03:29:40 by ml-hote           #+#    #+#             */
/*   Updated: 2026/08/26 21:50:06 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Parser.hpp"
#include "../../headers/Commands.hpp"

std::string	Server::getPassword() const
{
	return (this->_password);
}

int	Server::getPort() const
{
	return (this->_port);
}

int	Server::getSocket() const
{
	return (this->_socket);
}
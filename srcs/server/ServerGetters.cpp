/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerGetters.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 03:29:40 by ml-hote           #+#    #+#             */
/*   Updated: 2026/08/25 00:11:12 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Parser.hpp"
#include "../../headers/Commands.hpp"

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
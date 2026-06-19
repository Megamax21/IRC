/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerGetters.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 03:29:40 by ml-hote           #+#    #+#             */
/*   Updated: 2026/06/19 03:30:48 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Server.hpp"

std::string	Server::get_password()
{
	return (this->_password);
}

int	Server::get_port()
{
	return (this->_port);
}

int	Server::get_socket()
{
	return (this->_socket);
}
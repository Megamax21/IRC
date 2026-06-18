/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:45 by ml-hote           #+#    #+#             */
/*   Updated: 2026/06/19 00:33:55 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

int main(int ac, char **av)
{
	Server *irc_server = new Server();
	irc_server->server_launching();
	(void) ac;
	(void) av;
	return 0;
}
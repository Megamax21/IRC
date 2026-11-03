/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:45 by ml-hote           #+#    #+#             */
/*   Updated: 2026/11/03 15:52:30 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

int main(int ac, char **av)
{
	std::cout << "Before parsing" << std::endl;
	if (!argsParsing(ac, av))
		return (-1);
	std::cout << "Parsing is finished" << std::endl;
	Server *irc_server = new Server(atoi(av[1]), av[2]);
	irc_server->serverLaunching();
	delete irc_server;
	std::cout << "test" << std::endl;
	return (0);
}
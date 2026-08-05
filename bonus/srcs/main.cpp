/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:45 by ml-hote           #+#    #+#             */
/*   Updated: 2026/07/12 17:47:41 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"
#include "../headers/GambleBot.hpp"
int main(int ac, char **av)
{
	std::cout << "Before parsing" << std::endl;
	if (!args_parsing(ac, av))
		return (-1);
	
	std::cout << "Testing bot" << std::endl;
	srand(time(0));
	GambleBot gb = GambleBot();
	gb.pickCards(2);
	std::cout << "Parsing is finished" << std::endl;
	Server *irc_server = new Server(atoi(av[1]), av[1]);
	irc_server->server_launching();
	return (0);
}
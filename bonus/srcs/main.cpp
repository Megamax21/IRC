/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:45 by ml-hote           #+#    #+#             */
/*   Updated: 2026/08/26 21:51:47 by sbehar           ###   ########.fr       */
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
	return (0);
}
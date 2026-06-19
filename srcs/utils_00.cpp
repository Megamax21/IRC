/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 03:53:12 by ml-hote           #+#    #+#             */
/*   Updated: 2026/06/19 04:33:06 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/utils_00.hpp"

bool	is_good_irc_port(char *s_port)
{
	int i = 0;
	while (s_port[i])
	{
		if (!isdigit(s_port[i]))
		{
			std::cout << "Port has a non-digit character : " << s_port[i] << std::endl;
			return (false);
		}
		i++;
	}
	int i_port = atoi(s_port);
	if (i_port > 6669 || i_port < 6665)
	{
		std::cout << "Port should be in range [6665 - 6669]" << std::endl;
		return (false);
	}
	return (true);
}

bool	args_parsing(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Usage is : ./ircserv <port> <password>" << std::endl;
		return (false);
	}
	return (is_good_irc_port(av[1]));
}
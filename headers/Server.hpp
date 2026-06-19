/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:38 by ml-hote           #+#    #+#             */
/*   Updated: 2026/06/19 02:42:04 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils_00.hpp"

class Server
{
private:
	std::string	password;
	int			server_socket;
	struct		sockaddr_in  server_address;
public:
	Server();
	~Server();
	
	void	server_launching();
	// Getters

	// Setters
	void	set_server_socket(int ip);
	
	// Server creation methods :
	bool	create_socket();
	bool	bind_socket();
	bool	start_listening();
	int		accept_client();
	void	handle_client(int clientSocket);
	
	
};

#endif
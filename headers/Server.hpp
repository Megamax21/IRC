/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:38 by ml-hote           #+#    #+#             */
/*   Updated: 2026/06/19 04:36:13 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils_00.hpp"

class Server
{
private:
	std::string	_password;
	int			_socket;
	int			_port;
	struct		sockaddr_in _address;
public:
	Server();
	Server(int port, std::string password);
	~Server();
	
	// Getters
	std::string	get_password();
	int			get_socket();
	int			get_port();

	// Server creation methods :
	void	server_launching();
	bool	create_socket();
	bool	bind_socket();
	bool	start_listening();
	int		accept_client();
	void	handle_client(int clientSocket);
	
	
};

#endif
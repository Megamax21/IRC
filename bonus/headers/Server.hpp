/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:38 by ml-hote           #+#    #+#             */
/*   Updated: 2026/07/10 11:00:56 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils_00.hpp"
#include <map>

class Client;

class Server
{
private:
	std::string	_password;
	int			_socket;
	int			_port;
	struct		sockaddr_in _address;
	std::vector<int>	_quitClients;
public:
	Server();
	Server(int port, std::string password);
	~Server();
	
	// Getters
	std::string	get_password();
	int     get_socket();
	int     get_port();

	// Server creation methods :
	void	server_launching();
	bool	create_socket();
	bool	bind_socket();
	bool	start_listening();
	int		accept_client();
	bool	handle_client(int clientSocket);
	void	queue_message(int clientSocket, const std::string& message);
	bool	is_nick_taken(const std::string& nickname, int currentFd);
	bool	is_quit_client(int clientSocket);
	void	mark_quit_client(int clientSocket);
	void	unmark_quit_client(int clientSocket);
	
	
};

#endif

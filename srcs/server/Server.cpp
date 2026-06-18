/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:44 by ml-hote           #+#    #+#             */
/*   Updated: 2026/06/19 01:10:11 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Server.hpp"

Server::Server() : server_socket(0)
{
	std::cout << "Server constructor called" << std::endl;
}

Server::~Server()
{
}

/*	create_socket()

	socket(AF_INET, SOCK_STREAM, 0):
	AF_INET : IPv4 Internet protocols
	SOCK_STREAM : Provides sequenced, reliable, two-way, connection-based
			byte streams
	
	setsockopt: configure the socket's behavior
	
	create_socket uses socket and setsockopt to create a socket that
	when you kill and restart your server quickly, the port stays
	in a TIME_WAIT state for ~60 seconds
*/
bool Server::create_socket()
{
	this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_socket < 0)
	{
		std::cerr << "Error: socket() failed" << std::endl;
		return false;
	}
	int opt = 1;
	if (setsockopt(this->server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Error: setsockopt() failed" << std::endl;
		return false;
	}
	return true;
}

/*	bind_socket()

	Before binding, server_address is filled in:
	sin_family      : AF_INET, must match the family used in socket()
	sin_port        : the port to listen on, converted to network byte
			order with htons() (Host TO Network Short)
	sin_addr.s_addr : INADDR_ANY means "listen on all available network
			interfaces" (not just one specific IP)

	bind(): attaches the socket to this address/port combination, so
	the OS knows that incoming traffic on this port belongs to this
	socket.

	bind_socket() configures server_address and binds server_socket
	to it, preparing the socket to later listen for connections.
*/
bool Server::bind_socket()
{
	this->server_address.sin_family = AF_INET;
	this->server_address.sin_port = htons(6767);
	this->server_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(this->server_socket, (struct sockaddr*)&this->server_address, sizeof(this->server_address)) < 0)
	{
		std::cerr << "Error: bind() failed" << std::endl;
		return false;
	}
	return true;
}
/*	start_listening()

	listen(): marks server_socket as passive, meaning it will be used
	to accept incoming connections rather than to initiate one.
	SOMAXCONN is the system-defined maximum length for the queue of
	pending connections (clients that have connected but haven't been
	accept()ed yet).

	start_listening() puts the socket into listening mode so the OS
	starts queuing incoming connection requests on this port.
*/
bool Server::start_listening()
{
	if (listen(this->server_socket, SOMAXCONN) < 0)
	{
		std::cerr << "Error: listen() failed" << std::endl;
		return false;
	}
	std::cout << "Server listening on port 6767..." << std::endl;
	return true;
}

/*	accept_client()

	accept(): takes the first pending connection from the queue
	created by listen(), and returns a NEW socket dedicated to that
	client. server_socket keeps listening for other clients; this new
	socket is used to actually exchange data with the one we just
	accepted.
	clientAddress / clientLen : filled in by accept() with the
	connecting client's IP/port information.
	inet_ntoa(): converts the client's binary IP address into a
	human-readable string (e.g. "127.0.0.1").

	accept_client() blocks until a client connects, then returns a
	socket fd representing that specific client's connection.
*/
int Server::accept_client()
{
	struct sockaddr_in clientAddress;
	socklen_t clientLen = sizeof(clientAddress);

	int clientSocket = accept(this->server_socket, (struct sockaddr*)&clientAddress, &clientLen);
	if (clientSocket < 0)
	{
		std::cerr << "Error: accept() failed" << std::endl;
		return -1;
	}
	std::cout << "New client connected: " << inet_ntoa(clientAddress.sin_addr) << std::endl;
	return clientSocket;
}

/*	handle_client()

	recv(): reads data sent by the client into buffer, and returns the
	number of bytes actually read (or <= 0 if the client disconnected
	or an error occurred).
	send(): writes data back to the client through clientSocket — here
	it echoes back exactly what was received.
	close(): releases the client's socket once the exchange is done,
	since this server currently handles one message per connection.

	handle_client() reads one message from a connected client, echoes
	it back, then closes that client's connection.
*/
void Server::handle_client(int clientSocket)
{
	char buffer[1024] = {0};
	int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (bytesRead > 0)
	{
		std::cout << "Received: " << buffer << std::endl;
		send(clientSocket, buffer, bytesRead, 0);
	}
	close(clientSocket);
}

/*	server_launching()

	Runs the setup steps in order — create_socket(), bind_socket(),
	start_listening() — aborting immediately if any of them fails,
	since each one depends on the previous step having succeeded.

	Once setup succeeds, it enters an infinite loop: accept_client()
	blocks until a client connects, then handle_client() processes
	that one client fully before the loop goes back to accept the
	next one (the server is single-threaded and handles one client
	at a time).

	server_launching() is the entry point that brings the socket from
	creation to actively serving clients.
*/
void Server::server_launching()
{
	if (!create_socket())
		return;
	if (!bind_socket())
		return;
	if (!start_listening())
		return;

	while (true)
	{
		int clientSocket = accept_client();
		if (clientSocket < 0)
			continue;
		handle_client(clientSocket);
	}

	close(this->server_socket);
}

void	Server::set_server_socket(int ip)
{
	this->server_socket = ip;
}
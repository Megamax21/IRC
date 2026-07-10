/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerLauncher.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 03:23:23 by ml-hote           #+#    #+#             */
/*   Updated: 2026/07/06 16:47:18 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Server.hpp"
#include "../../headers/Client.hpp"
#include "../../headers/Parser.hpp"
#include "../../headers/CommandHandler.hpp"

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
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket < 0)
	{
		std::cerr << "Error: socket() failed" << std::endl;
		return false;
	}
	int opt = 1;
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Error: setsockopt() failed" << std::endl;
		return false;
	}
	return true;
}

/*	bind_socket()

	Before binding, _address is filled in:
	sin_family      : AF_INET, must match the family used in socket()
	sin_port        : the port to listen on, converted to network byte
			order with htons() (Host TO Network Short)
	sin_addr.s_addr : INADDR_ANY means "listen on all available network
			interfaces" (not just one specific IP)

	bind(): attaches the socket to this address/port combination, so
	the OS knows that incoming traffic on this port belongs to this
	socket.

	bind_socket() configures _address and binds _socket
	to it, preparing the socket to later listen for connections.
*/
bool Server::bind_socket()
{
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(this->_port);
	this->_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(this->_socket, (struct sockaddr*)&this->_address, sizeof(this->_address)) < 0)
	{
		std::cerr << "Error: bind() failed" << std::endl;
		return false;
	}
	return true;
}
/*	start_listening()

	listen(): marks _socket as passive, meaning it will be used
	to accept incoming connections rather than to initiate one.
	SOMAXCONN is the system-defined maximum length for the queue of
	pending connections (clients that have connected but haven't been
	accept()ed yet).

	start_listening() puts the socket into listening mode so the OS
	starts queuing incoming connection requests on this port.
*/
bool Server::start_listening()
{
	if (listen(this->_socket, SOMAXCONN) < 0)
	{
		std::cerr << "Error: listen() failed" << std::endl;
		return false;
	}
	std::cout << "Server listening on port "<< ntohs(this->_address.sin_port) <<"..." << std::endl;
	return true;
}

/*	accept_client()

	accept(): takes the first pending connection from the queue
	created by listen(), and returns a NEW socket dedicated to that
	client. _socket keeps listening for other clients; this new
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

	int clientSocket = accept(this->_socket, (struct sockaddr*)&clientAddress, &clientLen);
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
bool Server::handle_client(int clientSocket)
{
    char buffer[512];

    memset(buffer, 0, sizeof(buffer));

    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead <= 0)
    {
        std::cout << "Client " << clientSocket << " disconnected" << std::endl;
        return false;
    }

    Client* client = get_client(clientSocket);

    if (client == NULL)
        return false;

    client->append_input(std::string(buffer, bytesRead));

    while (Parser::hasCompleteCommand(*client))
    {
        std::string line = Parser::extractCommand(*client);
        IRCMessage message = Parser::parseLine(line);

        CommandHandler::execute(*this, *client, message);
    }

    return true;
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
    struct pollfd serverPoll;

    if (!create_socket())
        return;
    if (!bind_socket())
        return;
    if (!start_listening())
        return;

    this->_pollFds.clear();

    serverPoll.fd = this->_socket;
    serverPoll.events = POLLIN;
    serverPoll.revents = 0;
    this->_pollFds.push_back(serverPoll);

    while (true)
    {
        int ready = poll(&this->_pollFds[0], this->_pollFds.size(), -1);

        if (ready < 0)
        {
            std::cerr << "Error: poll() failed" << std::endl;
            continue;
        }

        for (std::vector<struct pollfd>::size_type i = 0; i < this->_pollFds.size();)
        {
            int fd = this->_pollFds[i].fd;
            short revents = this->_pollFds[i].revents;

            if (revents == 0)
            {
                ++i;
                continue;
            }

            if (revents & (POLLERR | POLLHUP | POLLNVAL))
            {
                if (fd != this->_socket)
                    remove_client(fd);

                this->_pollFds.erase(this->_pollFds.begin() + i);
                continue;
            }

            if (fd == this->_socket)
            {
                if (revents & POLLIN)
                {
                    int clientSocket = accept_client();

                    if (clientSocket >= 0)
                    {
                        add_client(clientSocket);

                        struct pollfd clientPoll;
                        clientPoll.fd = clientSocket;
                        clientPoll.events = POLLIN;
                        clientPoll.revents = 0;

                        this->_pollFds.push_back(clientPoll);
                    }
                }

                ++i;
                continue;
            }

            if (revents & POLLIN)
            {
                if (!handle_client(fd))
                {
                    remove_client(fd);
                    this->_pollFds.erase(this->_pollFds.begin() + i);
                    continue;
                }
            }

            if (revents & POLLOUT)
            {
                if (!send_queued_messages(fd))
                {
                    remove_client(fd);
                    this->_pollFds.erase(this->_pollFds.begin() + i);
                    continue;
                }
            }

            this->_pollFds[i].revents = 0;
            ++i;
        }
    }

    close(this->_socket);
}

void Server::add_client(int clientSocket)
{
    _clients[clientSocket] = new Client(clientSocket);
}

void Server::remove_client(int clientSocket)
{
    std::map<int, Client*>::iterator it;

    it = _clients.find(clientSocket);
    if (it != _clients.end())
    {
        delete it->second;
        _clients.erase(it);
    }

    close(clientSocket);
}

Client* Server::get_client(int clientSocket)
{
    std::map<int, Client*>::iterator it;

    it = _clients.find(clientSocket);
    if (it == _clients.end())
        return NULL;

    return it->second;
}

bool Server::is_nickname_taken(const std::string& nickname,
    int currentClientSocket) const
{
    std::map<int, Client*>::const_iterator it;

    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->first != currentClientSocket
            && it->second->get_nickname() == nickname)
            return true;
    }
    return false;
}

void Server::disable_pollout(int clientSocket)
{
    for (size_t i = 0; i < _pollFds.size(); ++i)
    {
        if (_pollFds[i].fd == clientSocket)
        {
            _pollFds[i].events &= ~POLLOUT;
            return;
        }
    }
}

void Server::enable_pollout(int clientSocket)
{
    for (size_t i = 0; i < _pollFds.size(); ++i)
    {
        if (_pollFds[i].fd == clientSocket)
        {
            _pollFds[i].events |= POLLOUT;
            return;
        }
    }
}

void Server::queue_message(int clientSocket, const std::string& message)
{
    Client* client;

    client = get_client(clientSocket);
    if (client == NULL)
        return;

    client->append_output(message);
    enable_pollout(clientSocket);
}

bool Server::send_queued_messages(int clientSocket)
{
    Client* client;

    client = get_client(clientSocket);
    if (client == NULL)
        return false;

    std::string& output = client->get_output_buffer();

    if (output.empty())
    {
        disable_pollout(clientSocket);
        return true;
    }

    ssize_t bytesSent = send(clientSocket, output.c_str(), output.size(), 0);

    if (bytesSent <= 0)
        return false;

    output.erase(0, bytesSent);

    if (output.empty())
        disable_pollout(clientSocket);

    return true;
}
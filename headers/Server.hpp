/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:38 by ml-hote           #+#    #+#             */
/*   Updated: 2026/07/06 16:47:43 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils_00.hpp"
#include <map>
#include <vector>
#include <poll.h>

class Client;

class Server
{
private:
    std::string                 _password;
    int                         _socket;
    int                         _port;
    struct sockaddr_in          _address;

    std::vector<int>            _quitClients;

    std::map<int, Client*>      _clients;
    std::vector<struct pollfd>  _pollFds;

public:
    Server();
    Server(int port, std::string password);
    ~Server();

    // Getters
    std::string get_password() const;
    int         get_socket() const;
    int         get_port() const;

    // Server creation methods
    void    server_launching();
    bool    create_socket();
    bool    bind_socket();
    bool    start_listening();
    int     accept_client();
    bool    handle_client(int clientSocket);

    // Client storage
    void    add_client(int clientSocket);
    void    remove_client(int clientSocket);
    Client* get_client(int clientSocket);

    bool    is_nickname_taken(const std::string& nickname,
                int currentClientSocket) const;

    // Output queue
    void    queue_message(int clientSocket, const std::string& message);
    void    enable_pollout(int clientSocket);
    void    disable_pollout(int clientSocket);
    bool    send_queued_messages(int clientSocket);

    // Quit
    bool    is_quit_client(int clientSocket);
    void    mark_quit_client(int clientSocket);
    void    unmark_quit_client(int clientSocket);
};

#endif
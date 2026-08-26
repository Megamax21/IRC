/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:38 by ml-hote           #+#    #+#             */
/*   Updated: 2026/08/26 22:09:55 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils_00.hpp"
#include "Channel.hpp"
#include <map>
#include <vector>
#include <poll.h>

class Client;

class Server
{
private:
    std::string                     _password;
    int                             _socket;
    int                             _port;
    struct sockaddr_in              _address;

    std::vector<int>                _quitClients;

    std::map<int, Client*>          _clients;
    std::map<std::string, Channel>  _channels;
    std::vector<struct pollfd>      _pollFds;

public:
    Server();
    Server(int port, std::string password);
    ~Server();

    // Getters
    std::string getPassword() const;
    int         getSocket() const;
    int         getPort() const;

    // Server creation methods
    void    serverLaunching();
    bool    createSocket();
    bool    bindSocket();
    bool    startListening();
    int     acceptClient();
    bool    handleClient(int clientSocket);

    // Client storage
    void    addClient(int clientSocket);
    void    removeClient(int clientSocket);
    void    sendToClient(Client *client, const std::string &message);
    Client* getClient(int clientSocket);
    Client* getClientByNickname(const std::string& nickname);

    bool    isNicknameTaken(const std::string& nickname,
                int currentClientSocket) const;

    // Channel storage
    Channel* getChannel(const std::string& name);
    Channel* createChannel(const std::string& name);
    void     sendToChannel(Channel *channel, const std::string &message, Client *except);
    void     removeClientFromAllChannels(Client *client);
    void     broadcastToChannel(Channel *channel, const std::string &message);

    // Output queue
    void    queueMessage(int clientSocket, const std::string& message);
    void    enablePollout(int clientSocket);
    void    disablePollout(int clientSocket);
    bool    sendQueuedMessages(int clientSocket);

    // Quit
    bool    isQuitClient(int clientSocket);
    void    markQuitClient(int clientSocket);
    void    unmarkQuitClient(int clientSocket);
};

#endif
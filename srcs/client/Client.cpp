/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:26:48 by sbehar            #+#    #+#             */
/*   Updated: 2026/07/06 22:26:48 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Client.hpp"

Client::Client(int fd)
    : _fd(fd),
      _nickname(""),
      _username(""),
      _realname(""),
      _passwordAccepted(false),
      _registered(false),
      _inputBuffer(""),
      _outputBuffer("")
{
}

Client::~Client()
{
}

int Client::getFd() const
{
    return _fd;
}

const std::string& Client::getNickname() const
{
    return _nickname;
}

const std::string& Client::getUsername() const
{
    return _username;
}

const std::string& Client::getRealname() const
{
    return _realname;
}

std::string Client::getPrefix() const
{
    return (":" + _nickname + "!" + _username + "@localhost");
}

void Client::setNickname(const std::string& nickname)
{
    _nickname = nickname;
}

void Client::setUsername(const std::string& username)
{
    _username = username;
}

void Client::setRealname(const std::string& realname)
{
    _realname = realname;
}

bool Client::isPasswordAccepted() const
{
    return _passwordAccepted;
}

void Client::setPasswordAccepted(bool value)
{
    _passwordAccepted = value;
}

bool Client::isRegistered() const
{
    return _registered;
}

void Client::setRegistered(bool value)
{
    _registered = value;
}

bool Client::hasNickname() const
{
    return !_nickname.empty();
}

bool Client::hasUsername() const
{
    return !_username.empty();
}

void Client::appendInput(const std::string& data)
{
    _inputBuffer += data;
}

std::string& Client::getInputBuffer()
{
    return _inputBuffer;
}

void Client::appendOutput(const std::string& data)
{
    _outputBuffer += data;
}

std::string& Client::getOutputBuffer()
{
    return _outputBuffer;
}
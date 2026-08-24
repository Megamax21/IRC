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

#include "../headers/Client.hpp"

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

int Client::get_fd() const
{
    return _fd;
}

const std::string& Client::get_nickname() const
{
    return _nickname;
}

const std::string& Client::get_username() const
{
    return _username;
}

const std::string& Client::get_realname() const
{
    return _realname;
}

void Client::set_nickname(const std::string& nickname)
{
    _nickname = nickname;
}

void Client::set_username(const std::string& username)
{
    _username = username;
}

void Client::set_realname(const std::string& realname)
{
    _realname = realname;
}

bool Client::is_password_accepted() const
{
    return _passwordAccepted;
}

void Client::set_password_accepted(bool value)
{
    _passwordAccepted = value;
}

bool Client::is_registered() const
{
    return _registered;
}

void Client::set_registered(bool value)
{
    _registered = value;
}

bool Client::has_nickname() const
{
    return !_nickname.empty();
}

bool Client::has_username() const
{
    return !_username.empty();
}

void Client::append_input(const std::string& data)
{
    _inputBuffer += data;
}

std::string& Client::get_input_buffer()
{
    return _inputBuffer;
}

void Client::append_output(const std::string& data)
{
    _outputBuffer += data;
}

std::string& Client::get_output_buffer()
{
    return _outputBuffer;
}
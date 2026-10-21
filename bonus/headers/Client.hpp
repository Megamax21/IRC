/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:27:12 by sbehar            #+#    #+#             */
/*   Updated: 2026/07/06 22:27:12 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Client
{
private:
    int         _fd;

    std::string _nickname;
    std::string _username;
    std::string _realname;

    bool        _passwordAccepted;
    bool        _registered;

    std::string _inputBuffer;
    std::string _outputBuffer;

public:
    Client(int fd);
    ~Client();

    int getFd() const;

    const std::string& getNickname() const;
    const std::string& getUsername() const;
    const std::string& getRealname() const;
    std::string        getPrefix() const;

    void setNickname(const std::string& nickname);
    void setUsername(const std::string& username);
    void setRealname(const std::string& realname);

    bool isPasswordAccepted() const;
    void setPasswordAccepted(bool value);

    bool isRegistered() const;
    void setRegistered(bool value);

    bool hasNickname() const;
    bool hasUsername() const;

    void appendInput(const std::string& data);
    std::string& getInputBuffer();

    void appendOutput(const std::string& data);
    std::string& getOutputBuffer();
};
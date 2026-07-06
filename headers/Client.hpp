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

    int get_fd() const;

    const std::string& get_nickname() const;
    const std::string& get_username() const;
    const std::string& get_realname() const;

    void set_nickname(const std::string& nickname);
    void set_username(const std::string& username);
    void set_realname(const std::string& realname);

    bool is_password_accepted() const;
    void set_password_accepted(bool value);

    bool is_registered() const;
    void set_registered(bool value);

    bool has_nickname() const;
    bool has_username() const;

    void append_input(const std::string& data);
    std::string& get_input_buffer();

    void append_output(const std::string& data);
    std::string& get_output_buffer();
};
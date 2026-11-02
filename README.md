*This project has been created as part of the 42 curriculum by @tanton, @sbehar, @ml-hote*

# ft_irc 💬

## Description

**ft_irc** is an Internet Relay Chat (IRC) server written in **C++98** as part of the 42 curriculum.  
The goal of the project is to implement a real IRC server that can handle multiple clients simultaneously without blocking, using TCP/IP sockets and non-blocking I/O.

The server allows users to authenticate, choose a nickname, join channels, exchange public and private messages, and manage channels through operator commands. It follows the core behavior of the IRC protocol.

### Main features

- Multiple simultaneous client connections
- TCP/IP communication using sockets
- Non-blocking I/O with a single `poll()` loop
- User authentication with `PASS`, `NICK`, and `USER`
- Channel creation and management with `JOIN` and `TOPIC`
- Public and private messaging with `PRIVMSG`
- Channel operator privileges
- Operator commands: `KICK`, `INVITE`, `TOPIC`, and `MODE`
- Channel modes: `i`, `t`, `k`, `o`, and `l`
- Handling of partial messages and client disconnections
- Graceful shutdown and memory cleanup

## Instructions

### Requirements

- A Unix-like operating system
- `make`
- A C++98-compatible compiler, such as `g++` or `clang++`
- An IRC client such as **WeeChat**, **HexChat**, **irssi**, or `nc` / `netcat` for testing

### Compilation

Clone the repository and build the project:

```bash
git clone [https://github.com/Megamax21/IRC]
cd ft_irc
make
```

Useful Makefile targets:

```bash
make        # Compile the server
make clean  # Remove object files
make fclean # Remove object files and the executable
make re     # Rebuild the project from scratch
```

### Execution

Run the server with a port number and a connection password:

```bash
./ircserv <port> <password>
```

Example:

```bash
./ircserv 6667 mypassword
```

- `<port>` must be an available TCP port, for example `6667`
- `<password>` is the password clients must provide

### Connecting with netcat

Open another terminal and connect to the server:

```bash
nc localhost 6667
```

Then authenticate and interact with the server:

```text
PASS mypassword
NICK alice
USER alice 0 * :Alice
JOIN #42
PRIVMSG #42 :Hello everyone!
```

### Connecting with an IRC client

In an IRC client such as Hexchat:

1. Add a new IRC server.
2. Set the address to `localhost` or `127.0.0.1` and the port to `6667`.
3. Set the server password to `mypassword`.
4. Connect, choose a nickname, and join a channel:

```text
/join #42
```

## Usage examples

| Command | Example | Description |
|---|---|---|

| `JOIN` | `/join #general` | Joins or creates a channel |

| `JOIN` | `/join #a,#b,#c` | Joins several channels |

| `JOIN` | `/join #secret mypassword` | Joins a key-protected channel |

| `PRIVMSG` | `/privmsg #general :Hello!` | Sends a message to a channel |

| `PRIVMSG` | `/privmsg alice :Hi!` | Sends a private message to a user |

| `TOPIC` | `/topic #general` | Displays the current topic |

| `TOPIC` | `/topic #general :Welcome!` | Sets the channel topic |

| `KICK` | `/kick #general bob :spam` | Removes a user from a channel |

| `INVITE` | `/invite bob #general` | Invites a user to a channel |

| `MODE` | `/mode #general` | Displays the current channel modes |

| `MODE` | `/mode #general +i` | Makes the channel invite-only |

| `MODE` | `/mode #general -i` | Disables invite-only mode |

| `MODE` | `/mode #general +t` | Restricts topic changes to channel operators |

| `MODE` | `/mode #general -t` | Allows any channel member to change the topic |

| `MODE` | `/mode #general +k secret` | Sets the channel key |

| `MODE` | `/mode #general -k secret` | Removes the channel key |

| `MODE` | `/mode #general +o charlie` | Gives operator status to a user |

| `MODE` | `/mode #general -o charlie` | Removes operator status from a user |

| `MODE` | `/mode #general +l 10` | Limits the channel to 10 members |

| `MODE` | `/mode #general -l` | Removes the member limit |

| `QUIT` | `/quit` | Disconnects from the server |

## Resources

- [Poll Command](https://man7.org/linux/man-pages/man2/poll.2.html)
- [IRC Commands](https://www.techbull.com/techbull/guide/internet/irccommande.html)
- [IRC Error Replies Codes](https://www.irchelp.org/protocol/rfc/chapter6.html)
- [IRC Protocol](https://mathieu-lemoine.developpez.com/tutoriels/irc/protocole/?page=commandes)
- [C++ Reference](https://en.cppreference.com/w/)
- [C++ Maps](https://www.geeksforgeeks.org/cpp/map-associative-containers-the-c-standard-template-library-stl/)
- [C++ Sockets](https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp)

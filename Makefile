NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98

SRCS = srcs/main.cpp \
		srcs/utils_00.cpp \
		srcs/Parser.cpp \
		srcs/server/Server.cpp \
		srcs/server/ServerLauncher.cpp \
		srcs/server/ServerGetters.cpp \
		srcs/client/Client.cpp \
		srcs/channel/Channel.cpp \
		srcs/commands/CommandHandler.cpp \
		srcs/commands/Join.cpp \
		srcs/commands/PrivMsg.cpp \
		srcs/commands/Kick.cpp \
		srcs/commands/Invite.cpp

HEADERS = headers/Server.hpp \
		  headers/utils_00.hpp \
		  headers/Client.hpp \
		  headers/Channel.hpp \
		  headers/Parser.hpp \
		  headers/Commands.hpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
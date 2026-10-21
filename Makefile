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
		srcs/commands/Invite.cpp \
		srcs/commands/Topic.cpp \
		srcs/commands/Mode.cpp

HEADERS = headers/Server.hpp \
		  headers/utils_00.hpp \
		  headers/Client.hpp \
		  headers/Channel.hpp \
		  headers/Parser.hpp \
		  headers/Commands.hpp

MANDATORY_SRCS = $(addprefix mandatory/,$(SRCS))
MANDATORY_HEADERS = $(addprefix mandatory/,$(HEADERS))
MANDATORY_OBJS = $(MANDATORY_SRCS:.cpp=.o)

# Mandatory
all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(MANDATORY_OBJS): mandatory/%.o: mandatory/%.cpp $(MANDATORY_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f $(MANDATORY_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

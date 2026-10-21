NAME = ircserv
BONUS_NAME = ircserv_bonus

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
BONUS_SRCS = $(addprefix bonus/,$(SRCS))
MANDATORY_HEADERS = $(addprefix mandatory/,$(HEADERS))
BONUS_HEADERS = $(addprefix bonus/,$(HEADERS))
MANDATORY_OBJS = $(MANDATORY_SRCS:.cpp=.o)
BONUS_OBJS = $(BONUS_SRCS:.cpp=.o)

# Mandatory
all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(MANDATORY_OBJS): mandatory/%.o: mandatory/%.cpp $(MANDATORY_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Bonus
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BONUS_OBJS): bonus/%.o: bonus/%.cpp $(BONUS_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re

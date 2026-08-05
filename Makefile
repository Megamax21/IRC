NAME = ircserv
BONUS_NAME = ircserv_bonus

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98

MANDATORY_SRCS = mandatory/srcs/main.cpp \
		mandatory/srcs/server/Server.cpp \
		mandatory/srcs/utils_00.cpp \
		mandatory/srcs/server/ServerLauncher.cpp \
		mandatory/srcs/server/ServerGetters.cpp

BONUS_SRCS = bonus/srcs/main.cpp \
		bonus/srcs/server/Server.cpp \
		bonus/srcs/utils_00.cpp \
		bonus/srcs/server/ServerLauncher.cpp \
		bonus/srcs/server/ServerGetters.cpp \
		bonus/srcs/CommandHandler.cpp \
		bonus/srcs/Parser.cpp \
		bonus/srcs/Client.cpp \
		bonus/srcs/channel/Channel.cpp \
		bonus/srcs/GambleBot.cpp
MANDATORY_OBJS = $(MANDATORY_SRCS:.cpp=.o)
BONUS_OBJS = $(BONUS_SRCS:.cpp=.o)
ALL_OBJS = $(MANDATORY_SRCS:.cpp=.o) $(BONUS_SRCS:.cpp=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(MANDATORY_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BONUS_NAME): $(BONUS_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(ALL_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus

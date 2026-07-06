NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98

SRCS = srcs/main.cpp \
		srcs/server/Server.cpp srcs/utils_00.cpp srcs/server/ServerLauncher.cpp \
		srcs/server/ServerGetters.cpp

HEADERS = headers/Server.hpp headers/utils_00.hpp

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
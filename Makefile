# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 10:51:07 by pageblanche       #+#    #+#              #
#    Updated: 2024/08/17 15:04:49 by pageblanche      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX            =    c++

NAME        =    a.out

LDFLAGS = -lSDL -lGL -lGLU

SRC            =     Main.cpp                	\
					 Map/Map.cpp                \
					 Map/Mainland.cpp           \
					 Land/Land.cpp              \
					 Land/Plains.cpp            \
					 Land/Water.cpp             \
					 Land/Sand.cpp              \
					 

OBJ            =     $(SRC:.cpp=.o)

CFLAGS        =     -Wall -Wextra -Werror -std=c++98 -g

all: $(NAME)

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $(<:.cpp=.o) 

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
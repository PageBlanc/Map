# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 10:51:07 by pageblanche       #+#    #+#              #
#    Updated: 2024/08/10 16:07:07 by pageblanche      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g

G++ = g++

NAME = a.out

Map = Map/Map.cpp Map/Mainland.cpp

Land = Land/Land.cpp Land/Plains.cpp

SRC = Main.cpp $(Map) $(Land)

OBJ = $(SRC:.cpp=.o)

# INC = Land/Land.hpp Land/Plains.hpp Map/Map.hpp Map/Mainland.hpp

all: $(NAME) #build/cpptest

# build:
# 	mkdir -p build

# build/cpptest: build/main.o | build
# 	@echo building $@
# 	g++ -o $@ $^

# build/main.o: main.cpp | build
# 	@echo building $@
# 	g++ -o $@ -c $^

$(NAME): $(OBJ)
	$(G++) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(G++) $(CFLAGS) -c $< $@
clean:
	rm -f $(OBJ)
	# rm -rf build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
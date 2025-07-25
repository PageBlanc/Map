# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 10:51:07 by pageblanche       #+#    #+#              #
#    Updated: 2025/07/25 14:51:54 by axdubois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX		= c++

NAME	= Map

LDFLAGS = -lSDL -lGL -lGLU

CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g -O2

SRC	= 	srcs/main.cpp					\
		srcs/SDL.cpp					\
		srcs/utils.cpp					\
		srcs/Map/Map.cpp				\
		srcs/Land/Land.cpp				\
		srcs/Land/Plains.cpp			\
		srcs/Land/Water.cpp				\
		srcs/Land/Sand.cpp				\
		srcs/Land/Mountain.cpp			\
		srcs/Land/Void.cpp				\
		srcs/Land/Hill.cpp				\
		srcs/Land/Ice.cpp				\
		srcs/Noise/PerlinNoise.cpp		\
		srcs/Object/Light.cpp			\

OBJ = $(patsubst srcs/%.cpp,objs/%.o,$(SRC))

all: $(NAME)

objs/%.o: srcs/%.cpp | objs
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -I Include -c $< -o $@

objs:
	@mkdir -p objs/Land objs/Map objs/Noise objs/Object

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	
clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
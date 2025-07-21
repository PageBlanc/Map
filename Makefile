# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axdubois <axdubois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 10:51:07 by pageblanche       #+#    #+#              #
#    Updated: 2025/07/21 20:04:18 by axdubois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX		= c++

NAME	= Map

LDFLAGS = -lSDL -lGL -lGLU

OBJ		= $(SRC:.cpp=.o)

CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g

SRC	= 	srcs/main.cpp					\
		srcs/SDL.cpp					\
		srcs/utils.cpp					\
		srcs/Map/Map.cpp				\
		srcs/Map/Mainland.cpp			\
		srcs/Map/Amplified.cpp			\
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

objs/%.o: srcs/%.cpp
	$(CXX) $(CFLAGS) -I Include -c $< -o $@

all: $(NAME)

.cpp.o:
	$(CXX) $(CFLAGS) -I Include -c $< -o objs/$(notdir $(<:.cpp=.o))

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	
clean:
	rm -f objs/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
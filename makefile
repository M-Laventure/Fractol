# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malavent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/22 15:27:13 by malavent          #+#    #+#              #
#    Updated: 2019/05/20 11:40:49 by malavent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
SRC_NAME = main.c tools.c mandelbrot.c julia.c events.c burningship.c init_fract.c
SRCS = $(addprefix srcs/, $(SRC_NAME))
OBJS = $(SRC_NAME:.c=.o)
HEADERS = -I includes/fractol.h
LXFLAGS = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
LFTFLAGS = libft/libft.a

#ifdef FLAGS
#	ifeq ($(FLAGS), none)
#	$(FLAGS)=

all: $(NAME)

$(NAME): lib 
	@echo "FRACTOL Compiling: \033[1;32mDONE\033[m"
	$(CC) -c $(CFLAGS) $(HEADERS) $(SRCS)
	$(CC) -o $(NAME) $(LXFLAGS) $(LFTFLAGS) $(OBJS)
	
lib : 
	make -C libft

clean :
	rm -rf $(OBJS)
	@echo "FRACTOL clean objects"

fclean : clean
	rm -rf $(NAME)
	@echo "FRACTOL clean objects + bin"

re : fclean all

.PHONY: clean fclean re all

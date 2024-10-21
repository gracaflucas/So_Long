# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 18:52:55 by lufiguei          #+#    #+#              #
#    Updated: 2024/09/07 18:52:56 by lufiguei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g

NAME = so_long

LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a
MLX = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm

SRC = main.c\
	parser.c\
	game_utils.c\
	render.c\
	game_utils2.c\
	
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(MINILIBX) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MINILIBX):
	$(MAKE) -C minilibx-linux

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx-linux clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re

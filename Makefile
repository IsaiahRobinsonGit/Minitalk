# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 09:41:54 by irobinso          #+#    #+#              #
#    Updated: 2025/02/04 11:06:09 by irobinso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

CLIENT = client
SERVER = server

all: $(NAME)

$(NAME): $(LIBFT) $(CLIENT) $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBFT_DIR) -lft

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

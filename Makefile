# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apolguil <apolguil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/10 16:08:53 by apolguil          #+#    #+#              #
#    Updated: 2026/05/10 16:08:54 by apolguil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= gnl
CC	= cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
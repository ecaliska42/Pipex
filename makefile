# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 16:37:34 by ecaliska          #+#    #+#              #
#    Updated: 2023/11/22 16:39:26 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=	cc

CFLAGS=	-Wall -Werror -Wextra -g

SRC=	pipex.c

NAME= pipex

RM= rm -f

$(NAME): $(SRC)
	make -C ./libft all
	make -C ./ft_printf all
	$(CC) $(CFLAG) -o $(NAME) $(SRC) libft/libft.a ft_printf/libftprintf.a

all: $(NAME)

clean:
	$(RM) $(OBJ)
	+$(MAKE) clean -C libft
	+$(MAKE) clean -C ft_printf

fclean: clean
	$(RM) $(NAME)
	+$(MAKE) fclean -C libft
	+$(MAKE) fclean -C ft_printf

re:	fclean all

.PHONY: all clean fclean re
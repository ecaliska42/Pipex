# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 16:37:34 by ecaliska          #+#    #+#              #
#    Updated: 2023/11/25 17:03:05 by ecaliska         ###   ########.fr        #
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
	make -C ./gnl all
	$(CC) $(CFLAG) -o $(NAME) $(SRC) libft/libft.a ft_printf/libftprintf.a gnl/get_next_line.a

all: $(NAME)

clean:
	$(RM) $(OBJ)
	+$(MAKE) clean -C libft
	+$(MAKE) clean -C ft_printf
	+$(MAKE) clean -C gnl

fclean: clean
	$(RM) $(NAME)
	+$(MAKE) fclean -C libft
	+$(MAKE) fclean -C ft_printf
	+$(MAKE) fclean -C gnl

re:	fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 16:37:34 by ecaliska          #+#    #+#              #
#    Updated: 2023/11/28 21:11:11 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=	cc

CFLAGS=	-Wall -Werror -Wextra

SRC=	pipex.c

NAME= pipex

RM= rm -f

$(NAME): $(SRC)
	make -C ./libft all
	make -C ./ft_printf all
	make -C ./ft_fd_printf all
	$(CC) $(CFLAG) -g -o $(NAME) $(SRC) libft/libft.a ft_printf/libftprintf.a ft_fd_printf/ft_fd_printf.a

all: $(NAME)

clean:
	$(RM) $(OBJ)
	+$(MAKE) clean -C libft
	+$(MAKE) clean -C ft_printf
	+$(MAKE) clean -C ft_fd_printf

fclean: clean
	$(RM) $(NAME)
	+$(MAKE) fclean -C libft
	+$(MAKE) fclean -C ft_printf
	+$(MAKE) fclean -C ft_fd_printf

re:	fclean all

.PHONY: all clean fclean re
CC=	cc

CFLAGS=	-Wall -Werror -Wextra

SRC=	get_next_line_bonus.c get_next_line_utils_bonus.c \
		get_next_line_utils.c get_next_line.c

OBJ= $(SRC:.c=.o)

NAME= get_next_line.a

RM= rm -f

all: $(NAME)

$(NAME):	$(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.cc
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean && make all

.PHONY: all clean fclean re

NAME =		philo
SRC	=		ft_atoi.c	ft_atol.c
OBJ	=		$(SRC:.c=.o)

CC	=		gcc
CFLAGS =	-Wall -Wextra -Werror
RM	=		rm -f

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(SRC)

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re

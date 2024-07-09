NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra

SOURCES = 	ft_atol.c \
			ft_atoi.c \
			ft_isdigit.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) -fsanitize=address -g

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCES:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	$(MAKE) all BONUS_FLAG=yes

.PHONY: all clean fclean re bonus

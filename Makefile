NAME = philo
CFLAGS = -Wall -Wextra -Werror -g
CLINKS = -I . -I ./libft
CLIBS = -L ./libft -lft
CFILES = $(wildcard *.c)
OBJS = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) 
	cc $(CFLAGS) $(CLIBS) $(CLINKS) $(OBJS) -o $(NAME)

%.o : %.c philo.h 
	cc $(CFLAGS) $(CLINKS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re


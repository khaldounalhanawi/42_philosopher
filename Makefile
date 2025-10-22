NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread -g
CLINKS = -I .
#CLIBS = -L ./libft -lft
CFILES = $(wildcard *.c)
OBJS = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) 
	cc $(CFLAGS) $(CLINKS) $(OBJS) -o $(NAME)

%.o : %.c philo.h 
	cc $(CFLAGS) $(CLINKS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re


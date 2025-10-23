NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread -g
CLINKS = -I .
CFILES = \
			fn_cleanup.c \
			fn_converters.c \
			fn_get_set_reset.c \
			fn_inits_I.c \
			fn_inits_II.c \
			fn_read_functions.c \
			fn_return_functions.c \
			fn_simulate_I.c \
			fn_simulate_II.c \
			fn_simulate_III.c \
			fn_simulate_IIII.c \
			fn_simulate_IIIII.c \
			fn_usleep_improve.c \
			main.c
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


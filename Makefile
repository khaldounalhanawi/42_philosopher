NAME = philo
CFLAGS = -Wall -Wextra -Werror
CLINKS = -I . -I ./libft
CLIBS = -L ./libft -lft
CFILES = $(wildcard *.c)
OBJS = $(CFILES:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(CLIBS) $(CLINKS) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all

%.o : %.c philo.h 
	cc $(CFLAGS) $(CLINKS) -c $< -o $@

clean :
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all clean fclean re


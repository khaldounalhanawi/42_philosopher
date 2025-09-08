# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
#include <stdlib.h>
# include <limits.h>
# include <pthread.h>
#include <time.h>
# include "libft.h"
#include <sys/time.h>

typedef struct s_phil
{
	int	name;
	int	fork;
	int	dead;
}	t_phil;

typedef struct s_settings
{
	int		n_ph;
	long	z_die;
	long	z_eat;
	long	z_sleep;
	int		n_eat;
}	t_settings;


long long	cnv_atol(const char *str);
long		*cnv_strarr_long(int argc, char **argv);
void		put_str(char *str);
int			return_int_msg(char *str, int val, long **lval_arr);
int			read_settings(t_settings *mysettings, int argc, char **argv);


# endif

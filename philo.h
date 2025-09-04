# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"
#include <sys/time.h>

typedef struct s_phil
{
	int	time_to_die;
	int	fork;

}t_phil;

typedef struct s_settings
{
	int		n_ph;
	long	z_die;
	long	z_eat;
	long	z_sleep;
	int		n_eat;
}	t_settings;


long	cnv_atol(const char *str);



# endif

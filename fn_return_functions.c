#include "philo.h"


int return_int_msg(char *str, int val, long **lval_arr)
{
	if (str)
	{
		while (*str)
		{
			write (1, str, 1);
			str ++;
		}
		write (1, "\n", 1);
	}
	if (lval_arr)
		free (*lval_arr);
	return (val);
}

void *return_null_str(char *str)
{
	printf ("%s", str);
	return (NULL);
}

// check if full? and exit??
int print_status(t_state state, t_phil *phil) // CHANGE TIME BACK TO MS
{
	unsigned long long	now;
	int					global_end;
	

	global_end = simulation_finished (phil->mysettings);
	if ( global_end == -1)
	{
		// if (pthread_mutex_unlock (&(phil->mysettings->mtx_print)) != 0)
		// 	return (-1);
		return (-1);
	}
	else if (global_end == 1)
	{
		// if (pthread_mutex_unlock (&(phil->mysettings->mtx_print)) != 0)
		// 	return (-1);
		return (1);
	}
	
	if (pthread_mutex_lock (&(phil->mysettings->mtx_print)) != 0)
		return (-1);

	reset_microsecond (&now); // check for fail

	if (state == DIED)
		printf ("%06llu %d has died\n", (now - phil->mysettings->start_sim) / 1000, phil->id);
	else if (state == EATING)
		printf (RED"%06llu %d is eating\n"RST, (now - phil->mysettings->start_sim) / 1000, phil->id);

	else if (state == SLEEPING)
		printf (G"%06llu %d is sleeping\n"RST, (now - phil->mysettings->start_sim) / 1000, phil->id);

	else if (state == THINKING)
		printf (B"%06llu %d is thinking\n"RST, (now - phil->mysettings->start_sim) / 1000, phil->id);
		
	else if (state == FORK1)
		printf ("%06llu %d has taken a fork:%d \n", (now - phil->mysettings->start_sim) / 1000, phil->id, phil->left_fork->fork_id);
	else if (state == FORK2)
		printf ("%06llu %d has taken a fork:%d \n", (now - phil->mysettings->start_sim) / 1000, phil->id, phil->right_fork->fork_id);


	if (pthread_mutex_unlock (&(phil->mysettings->mtx_print)) != 0)
		return (-1);
	return (1);
}

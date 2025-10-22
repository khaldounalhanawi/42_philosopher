#include "philo.h"

static int	create_all_threads(t_settings *mysettings)
{
	int	i;

	i = 0;
	if (mysettings->n_ph == 1)
		; // later
	else
	{
		while (i < mysettings->n_ph)
		{
			if( pthread_create (&(mysettings->arr_phil[i].thread),
				NULL, dinner_sim,
				(void *)&mysettings->arr_phil[i]) != 0)
				return (-1);
			i ++;
		}
	}
	if (pthread_create (&(mysettings->monitor),
				NULL, death_monitor,
				(void *)mysettings) != 0)
		return (-1);
	return (1);
}

static int	set_start_simulation(t_settings *mysettings)
{
	int		i;
	t_mutex	*this_mtx;

	i = 0;
	this_mtx = &(mysettings->arr_phil[i].mysettings->mtx_last_eat_time);
	while (i < mysettings->n_ph)
	{
		if (pthread_mutex_lock (this_mtx) == -1)
			return (-1);
		mysettings->arr_phil[i].last_meal_time = mysettings->start_sim;
		if (pthread_mutex_unlock (this_mtx) == -1)
			return (-1);
		i++ ;
	}
	return (1);
}

static int	join_all_threads(t_settings *mysettings)
{
	int	i;
	
	i = 0;
	while (i < mysettings->n_ph)
	{
		if( pthread_join (mysettings->arr_phil[i].thread,
			NULL) != 0)
			return (-1);
		i ++;
	}
	if (pthread_join (mysettings->monitor,
			NULL) != 0)
			return (-1);
	return (1);
}

int	simulate(t_settings *mysettings)
{
	if (mysettings->n_eat != -1 && mysettings->n_eat == 0)
	{
		printf ("Number of meals is 0\n");
		return (-1);
	}
	if (create_all_threads (mysettings) == -1)
		return (-1);
	if (reset_microsecond (&(mysettings->start_sim)) == -1)
		return (return_int_msg ("couldn't read time", -1, NULL));
	if (set_int_mtx (&(mysettings->mtx_ready_to_start), &(mysettings->all_threads_ready), 1) != 1)
		return (return_int_msg ("init sync failure", -1, NULL));
	if (set_start_simulation (mysettings) == -1)
		return (-1);
	if (join_all_threads (mysettings) == -1)
		return (-1);
	return (1);
}
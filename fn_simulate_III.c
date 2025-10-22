#include "philo.h"

static int	reorganize_forks_lock(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		if (pthread_mutex_lock(&phil->right_fork->fork) == -1)
			return (-1);
		print_status(FORK1, phil);
		if (pthread_mutex_lock(&phil->left_fork->fork) == -1)
			return (-1);
		print_status(FORK2, phil);
	}
	else
	{
		if (pthread_mutex_lock(&phil->left_fork->fork) == -1)
			return (-1);
		print_status(FORK1, phil);
		if (pthread_mutex_lock(&phil->right_fork->fork) == -1)
			return (-1);
		print_status(FORK2, phil);
	}
	return (1);
}

static int	reorganize_forks_unlock(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		if (pthread_mutex_unlock(&phil->right_fork->fork) == -1)
			return (-1);
		if (pthread_mutex_unlock(&phil->left_fork->fork) == -1)
			return (-1);
	}
	else
	{
		if (pthread_mutex_unlock(&phil->left_fork->fork) == -1)
			return (-1);
		if (pthread_mutex_unlock(&phil->right_fork->fork) == -1)
			return (-1);
	}
	return (1);
}

int	report_full(t_phil *phil)
{
	phil->meals_counter ++;
	if (phil->mysettings->n_eat != -1
		&& phil->meals_counter >= phil->mysettings->n_eat)
	{
		if (incriment_int_mtx(&(phil->mysettings->mtx_full_philosophers),
						&(phil->mysettings->full_philosophers_count)) == -1)
			return (-1);
		phil->full = 1;
		return (2);
	}
	else
		return (0);
}

int	eat_action(t_phil *phil)
{
	int	full_status;
	
	if (simulation_finished (phil->mysettings) == -1)
		return (-1);
	if (reorganize_forks_lock (phil) == -1)
		return (-1);
	if (pthread_mutex_lock (&(phil->mysettings->mtx_last_eat_time)) == -1)
		return (-1);
	if (reset_microsecond (&(phil->last_meal_time)) == -1)
		return (-1);
	if (pthread_mutex_unlock (&(phil->mysettings->mtx_last_eat_time)) == -1)
		return (-1);
	if (print_status (EATING, phil) == -1)
		return (-1);
	if (improved_usleep (phil->mysettings->z_eat, phil->mysettings) == -1)
		return (-1);
	if (reorganize_forks_unlock (phil) == -1)
		return (-1);
	full_status = report_full (phil);
	if (full_status != 0)
		return (full_status);
	return (1);
}

int	think_action(t_phil *philosopher)
{
	unsigned long long	extra_time;
	int	global_end_status;
	
	global_end_status = simulation_finished (philosopher->mysettings);
	if (global_end_status != 0)
		return (global_end_status);
	if (print_status (THINKING, philosopher) == -1)
		return (-1);
	extra_time = 0;
	if (philosopher->mysettings->n_ph % 2 != 0)
	{
		extra_time = philosopher->mysettings->z_eat / 2;
		if (extra_time < 0)
			extra_time = 0;
	}
	if (improved_usleep (extra_time , philosopher->mysettings) == -1)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_simulate_I.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:28 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/23 10:11:04 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_all_threads(t_settings *mysettings)
{
	int	i;

	i = 0;
	while (i < mysettings->n_ph)
	{
		if (pthread_create (&(mysettings->arr_phil[i].thread),
				NULL, dinner_sim,
				(void *)&mysettings->arr_phil[i]) != 0)
		{
			clear_threads_range (mysettings, 0, i);
			return (-1);
		}
		i ++;
	}
	if (pthread_create (&(mysettings->monitor),
			NULL, death_monitor,
			(void *)mysettings) != 0)
	{
		clear_threads_range (mysettings, 0, mysettings->n_ph);
		return (-1);
	}
	return (1);
}

static int	set_last_time_eat(t_settings *mysettings)
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
		if (pthread_join (mysettings->arr_phil[i].thread,
				NULL) != 0)
		{
			clear_threads_range (mysettings, i, mysettings->n_ph);
			return (-1);
		}
		i ++;
	}
	if (pthread_join (mysettings->monitor,
			NULL) != 0)
		return (-1);
	return (1);
}

int	simulate(t_settings *mysettings)
{
	if (create_all_threads (mysettings) == -1)
		return (-1);
	if (reset_microsecond (&(mysettings->start_sim)) == -1)
	{
		clear_threads_range (mysettings, 0, mysettings->n_ph);
		return (return_int_msg ("couldn't read time: start_sim", -1, NULL));
	}
	if (set_int_mtx (&(mysettings->mtx_ready_to_start),
			&(mysettings->all_threads_ready), 1) != 1)
	{
		clear_threads_range (mysettings, 0, mysettings->n_ph);
		return (return_int_msg ("init sync failure", -1, NULL));
	}
	if (set_last_time_eat (mysettings) == -1)
	{
		clear_threads_range (mysettings, 0, mysettings->n_ph);
		return (-1);
	}
	return (join_all_threads (mysettings));
}

// ./philo 6 800 400 200 | grep -v "fork"
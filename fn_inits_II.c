/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_inits_II.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:19 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/23 10:05:59 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fork_create(t_fork *myfork)
{
	if (pthread_mutex_init (&myfork->fork, NULL) != 0)
		return (return_int_msg("failed to initiate fork\n", -1, NULL));
	return (1);
}

int	init_forks(t_settings *mysettings)
{
	int	i;

	mysettings->arr_forks = malloc (sizeof (t_fork) * mysettings->n_ph);
	if (!mysettings->arr_forks)
		return (-1);
	i = 0 ;
	while (i < mysettings->n_ph)
	{
		mysettings->arr_forks[i].fork_id = i;
		if (fork_create (&mysettings->arr_forks[i]) == -1)
		{
			clear_forks (mysettings, i);
			return (-1);
		}
		i ++;
	}
	return (1);
}

static void	assign_forks(t_settings *mysettings, int pos)
{
	t_phil	*myphil;
	int		count;

	myphil = &mysettings->arr_phil[pos];
	count = mysettings->n_ph;
	myphil->left_fork = &mysettings->arr_forks[pos];
	myphil->right_fork = &mysettings->arr_forks[(pos + 1) % count];
}

int	init_phils(t_settings *mysettings)
{
	int	i;

	mysettings->arr_phil = malloc (sizeof (t_phil) * mysettings->n_ph);
	if (!mysettings->arr_phil)
		return (-1);
	i = 0;
	while (i < mysettings->n_ph)
	{
		mysettings->arr_phil[i].mysettings = mysettings;
		mysettings->arr_phil[i].id = i;
		mysettings->arr_phil[i].meals_counter = 0;
		mysettings->arr_phil[i].full = 0;
		mysettings->arr_phil[i].last_meal_time = 0;
		assign_forks (mysettings, i);
		i ++;
	}
	return (1);
}

int	init_mutexes(t_settings *mysettings)
{
	if (pthread_mutex_init (&(mysettings->mtx_ready_to_start), NULL) != 0)
		return (return_int_msg("failed to initiate mutex\n", -1, NULL));
	if (pthread_mutex_init (&(mysettings->mtx_end), NULL) != 0)
		return (return_int_msg("failed to initiate mutex\n", -1, NULL));
	if (pthread_mutex_init (&(mysettings->mtx_print), NULL) != 0)
		return (return_int_msg("failed to initiate mutex\n", -1, NULL));
	if (pthread_mutex_init (&(mysettings->mtx_full_philosophers), NULL) != 0)
		return (return_int_msg("failed to initiate mutex\n", -1, NULL));
	if (pthread_mutex_init (&(mysettings->mtx_last_eat_time), NULL) != 0)
		return (return_int_msg("failed to initiate mutex\n", -1, NULL));
	return (1);
}

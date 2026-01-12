/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:05 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/23 10:14:08 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_forks(t_settings	*mysettings, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (pthread_mutex_destroy (&(mysettings->arr_forks[i].fork)) != 0)
			printf ("failed to destroy: fork nr. %d\n", i);
		i ++;
	}
	free (mysettings->arr_forks);
}

void	clear_mysettings(t_settings	*mysettings)
{
	free (mysettings->end);
	if (pthread_mutex_destroy (&(mysettings->mtx_time)) != 0)
		printf ("failed to destroy: mtx_time\n");
	if (pthread_mutex_destroy (&(mysettings->mtx_full_philosophers)) != 0)
		printf ("failed to destroy: mtx_full_philosophers\n");
	if (pthread_mutex_destroy (&(mysettings->mtx_ready_to_start)) != 0)
		printf ("failed to destroy: mtx_ready_to_start\n");
	if (pthread_mutex_destroy (&(mysettings->mtx_end)) != 0)
		printf ("failed to destroy: mtx_end\n");
	if (pthread_mutex_destroy (&(mysettings->mtx_last_eat_time)) != 0)
		printf ("failed to destroy: mtx_last_eat_time\n");
	if (pthread_mutex_destroy (&(mysettings->mtx_print)) != 0)
		printf ("failed to destroy: mtx_print\n");
	clear_forks (mysettings, mysettings->n_ph);
	free (mysettings->arr_phil);
}

void	clear_threads_range(t_settings *mysettings, int start, int end)
{
	while (start < end)
	{
		pthread_detach (mysettings->arr_phil[start].thread);
		start++ ;
	}
}

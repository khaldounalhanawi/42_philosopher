/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_simulate_IIII.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:39 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/23 10:12:19 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	signal_death(t_phil *phil)
{
	if (print_status (DIED, phil) == -1)
		return (-1);
	if (set_int_mtx (&(phil->mysettings->mtx_end),
			phil->mysettings->end, 1) == -1)
		return (-1);
	return (1);
}

static int	die_check(t_phil *phil)
{
	unsigned long long	last;
	unsigned long long	now;

	if (get_long_mtx (&(phil->mysettings->mtx_last_eat_time),
			&(phil->last_meal_time), &last) == -1)
		return (-1);
	if (last == 0)
		return (0);
	if (reset_microsecond (&now) == -1)
		return (-1);
	if (now - last <= phil->mysettings->z_die)
		return (0);
	else
		return (signal_death (phil));
	return (0);
}

static int	are_all_full(t_settings *mysettings)
{
	int		k;
	t_mutex	*this_mtx;

	k = 0;
	this_mtx = &(mysettings->mtx_full_philosophers);
	if (get_int_mtx (this_mtx,
			&(mysettings->full_philosophers_count),
			&k) == -1)
		return (-1);
	if (k == mysettings->n_ph)
	{
		printf ("all are full! ********\n");
		if (set_int_mtx (&(mysettings->mtx_end), mysettings->end, 1) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

static int	run_monitor(t_settings *mysettings)
{
	int			all_are_full;
	int			i;
	int			death;

	death = 0;
	while (simulation_finished(mysettings) == 0)
	{
		i = 0;
		all_are_full = are_all_full (mysettings);
		if (all_are_full != 0)
			return (all_are_full);
		while (i < mysettings->n_ph && !simulation_finished(mysettings))
		{
			death = die_check (&(mysettings->arr_phil[i]));
			if (death != 0)
				return (death);
			i ++;
		}
		usleep (500);
	}
	return (3);
}

void	*death_monitor(void *p)
{
	t_settings	*mysettings;
	int			monitor_val;

	mysettings = (t_settings *) p;
	if (wait_for_all_start (mysettings) == -1)
		return (NULL);
	monitor_val = run_monitor (mysettings);
	if (monitor_val == -1)
		return (NULL);
	else
		return (NULL);
	return (NULL);
}

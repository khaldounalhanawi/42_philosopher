/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_simulate_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:31 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/23 10:11:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleep_action(t_phil *philosopher)
{
	int	global_end_status;

	global_end_status = simulation_finished (philosopher->mysettings);
	if (global_end_status != 0)
		return (global_end_status);
	if (print_status (SLEEPING, philosopher) == -1)
		return (-1);
	if (improved_usleep (philosopher->mysettings->z_sleep,
			philosopher->mysettings) == -1)
		return (-1);
	return (1);
}

static int	start_dinner(t_phil *philosopher)
{
	int	global_end_status;
	int	eat_status;
	int	sleep_status;
	int	think_status;

	while (!philosopher->full)
	{
		eat_status = eat_action (philosopher);
		if (eat_status != 1)
			return (eat_status);
		sleep_status = sleep_action (philosopher);
		if (sleep_status != 1)
			return (sleep_status);
		think_status = think_action (philosopher);
		if (think_status != 1)
			return (think_status);
		global_end_status = simulation_finished (philosopher->mysettings);
		if (global_end_status != 0)
			return (global_end_status);
	}
	return (1);
}

void	*dinner_sim(void *data)
{
	t_phil	*philosopher;

	philosopher = (t_phil *)data;
	if (wait_for_all_start (philosopher->mysettings) == -1)
		return (NULL);
	if (philosopher->id % 2 == 1)
		usleep(philosopher->mysettings->z_die / 4);
	if (start_dinner (philosopher) == -1)
		return (NULL);
	return (NULL);
}

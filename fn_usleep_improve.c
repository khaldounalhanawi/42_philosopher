/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_usleep_improve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:46 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/22 21:05:31 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	heavy_clock(unsigned long long start,
					unsigned long long input,
					t_settings *mysettings)
{
	unsigned long long	now;
	int					simulation_finish;

	if (reset_microsecond (&now) == -1)
		return (-1);
	while (now - start < input)
	{
		simulation_finish = simulation_finished (mysettings);
		if (simulation_finish != 0)
			return (simulation_finish);
		if (reset_microsecond (&now) == -1)
			return (-1);
		usleep (100);
	}
	return (1);
}

int	improved_usleep(unsigned long long input, t_settings *mysettings)
{
	unsigned long long	now;
	unsigned long long	start;
	int					simulation_finish;

	if (reset_microsecond (&start) == -1 || reset_microsecond (&now) == -1)
		return (-1);
	while (now - start < input)
	{
		simulation_finish = simulation_finished (mysettings);
		if (simulation_finish != 0)
			return (simulation_finish);
		if (reset_microsecond (&now) == -1)
			return (-1);
		if (input - (now - start) > 500)
			usleep (500);
		else
		{
			if (heavy_clock (start, input, mysettings) == -1)
				return (-1);
		}
	}
	return (1);
}

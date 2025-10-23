/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_simulate_IIIII.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:42 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/22 21:04:21 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_finished(t_settings *mysettings)
{
	int	val;

	val = 0;
	if (get_int_mtx (&(mysettings->mtx_end), mysettings->end, &val) == -1)
		return (-1);
	return (val);
}

int	wait_for_all_start(t_settings *mysettings)
{
	int	val;

	val = 0;
	while (val == 0)
	{
		if (get_int_mtx (&mysettings->mtx_ready_to_start,
				&mysettings->all_threads_ready, &val) == -1)
			return (-1);
	}
	return (1);
}

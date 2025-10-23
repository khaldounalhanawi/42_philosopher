/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_inits_I.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:16 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/22 20:52:42 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_settings(t_settings *mysettings)
{
	mysettings->end = malloc (sizeof (int));
	if (!mysettings->end)
		return (-1);
	*(mysettings->end) = 0;
	mysettings->start_sim = 0;
	mysettings->all_threads_ready = 0;
	if (init_forks (mysettings) != 1)
	{
		free (mysettings->end);
		return (-1);
	}
	if (init_phils (mysettings) != 1)
	{
		clear_forks (mysettings, mysettings->n_ph);
		return (-1);
	}
	init_mutexes (mysettings);
	return (1);
}

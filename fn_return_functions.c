/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_return_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:24 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/23 09:36:12 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_int_msg(char *str, int val, long **lval_arr)
{
	if (str)
	{
		while (*str)
		{
			write (1, str, 1);
			str ++;
		}
		write (1, "\n", 1);
	}
	if (lval_arr)
		free (*lval_arr);
	return (val);
}

void	*return_null_str(char *str)
{
	printf ("%s", str);
	return (NULL);
}

static void	dispatch_status(t_state state, t_phil *phil)
{
	unsigned long long	now;

	reset_microsecond (&now);
	if (state == DIED)
		printf ("%06llu %d has died\n",
			(now - phil->mysettings->start_sim) / 1000, phil->id + 1);
	else if (state == EATING)
		printf (RED"%06llu %d is eating\n"RST,
			(now - phil->mysettings->start_sim) / 1000, phil->id + 1);
	else if (state == SLEEPING)
		printf (G"%06llu %d is sleeping\n"RST,
			(now - phil->mysettings->start_sim) / 1000, phil->id + 1);
	else if (state == THINKING)
		printf (B"%06llu %d is thinking\n"RST,
			(now - phil->mysettings->start_sim) / 1000, phil->id + 1);
	else if (state == FORK)
		printf ("%06llu %d has taken a fork\n",
			(now - phil->mysettings->start_sim) / 1000, phil->id + 1);
}

int	print_status(t_state state, t_phil *phil)
{
	int	global_end;

	global_end = simulation_finished (phil->mysettings);
	if (global_end == -1)
		return (-1);
	else if (global_end == 1)
		return (1);
	if (pthread_mutex_lock (&(phil->mysettings->mtx_print)) != 0)
		return (return_int_msg ("@print_status: mutex_lock error", -1, NULL));
	dispatch_status (state, phil);
	if (pthread_mutex_unlock (&(phil->mysettings->mtx_print)) != 0)
		return (return_int_msg ("@print_status: mutex_unlock error", -1, NULL));
	return (1);
}

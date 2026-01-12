/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:48 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/23 10:26:58 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	run_solo(t_settings *mysettings)
{
	printf ("000000 1 has taken a fork\n");
	usleep (mysettings->z_die);
	printf ("%06llu 1 has died\n", mysettings->z_die);
	return (1);
}

static int	handle_special_cases(t_settings *mysettings)
{
	if (mysettings->n_eat != -1 && mysettings->n_eat == 0)
	{
		printf ("Number of meals is 0\n");
		return (-1);
	}
	if (mysettings->n_ph == 1)
		return (run_solo (mysettings));
	return (0);
}

int	main(int argc, char **argv)
{
	t_settings	mysettings;

	if (argc != 5 && argc != 6)
		return (return_int_msg ("Invalid number of arguments", -1, NULL));
	if (read_settings (&mysettings, argc, argv) != 1)
		return (-2);
	if (init_settings (&mysettings) != 1)
		return (-3);
	if (handle_special_cases (&mysettings) != 0)
	{
		clear_mysettings (&mysettings);
		return (-4);
	}
	simulate (&mysettings);
	clear_mysettings (&mysettings);
	return (1);
}

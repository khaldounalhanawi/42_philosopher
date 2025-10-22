#include "philo.h"

/*
 while loop the time
 */
static int	heavy_clock(unsigned long long	start,
					unsigned long long	input,
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
/*	clean	*/

/*
 1- uses Usleep until time is small
 1.1- constantly checking for finish of sim
 2- when time is smaller than 1000 mcs it uses while for accuracy
 */
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
		{
			// printf("usleep interrupted early (reason: sim finished)\n");
			return (simulation_finish);
		}
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
/*	clean	*/


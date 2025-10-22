#include "philo.h"

int	sleep_action(t_phil *philosopher)
{
	int	global_end_status;
	
	global_end_status = simulation_finished (philosopher->mysettings);
	if (global_end_status != 0)
		return (global_end_status);
	if (print_status (SLEEPING, philosopher) == -1)
		return (-1);
	if (improved_usleep (philosopher->mysettings->z_sleep, philosopher->mysettings) == -1)
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
	int		*error;

	philosopher = (t_phil *)data;
	error = malloc (sizeof (int));
	if (!error)
		return (NULL); // really?
	*error = -1;
	if (wait_for_all_start (philosopher->mysettings) == -1)
		return (error);
	if (philosopher->id % 2 == 1)
	{
		if (usleep(philosopher->mysettings->z_die / 4) == -1)
			return (error);
	}
	if (start_dinner (philosopher) == -1)
		return (error);
	return (NULL);
}


// pthread correct == 0!!!!!
// double check the times to fix the headache
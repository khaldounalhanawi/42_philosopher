#include "philo.h"

static int	value_checks(t_settings *mysettings, int argc)
{
	if (mysettings->n_ph <= 0
		|| mysettings->z_die <= 0
		|| mysettings->z_eat <= 0
		|| mysettings->z_sleep <= 0)
		return (return_int_msg ("Values can not be less than 1", -1, NULL));
	if (argc == 6 && mysettings->n_eat <= 0)
		return (return_int_msg ("Values can not be less than 1", -1, NULL));
	return (1);
}

int	read_settings(t_settings *mysettings, int argc, char **argv)
{
	long	*long_arr;

	long_arr = cnv_strarr_long (argc, argv);
	if (!long_arr)
		return (-1);
	if (long_arr[0] > INT_MAX)
		return (return_int_msg ("Too many philosophers", -1, &long_arr));
	mysettings->n_ph = (int) long_arr[0];
	mysettings->z_die = long_arr[1] * 1000;
	mysettings->z_eat = long_arr[2] * 1000;
	mysettings->z_sleep = long_arr[3] * 1000;
	if (argc == 6)
	{
		if (long_arr[4] > INT_MAX)
			return (return_int_msg ("eat count is too large", -1, &long_arr));
		mysettings->n_eat = (int) long_arr[4];
	}
	else
		mysettings->n_eat = -1;
	free (long_arr);
	return (value_checks (mysettings, argc));
}

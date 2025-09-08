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

static int	fn_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') 
			&& (str[i] != '-' && str[i] != '+'))
			return (0);
		i ++;
	}
	return (1);
}

static int	fn_isdigit_arr(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!fn_isdigit (argv[i]))
			return (0);
		i ++;
	}
	return (1);
}

int	read_settings(t_settings *mysettings, int argc, char **argv)
{
	long	*lval_arr;

	if (!fn_isdigit_arr (argc, argv))
		return (return_int_msg ("Bad input", -1, NULL));
	lval_arr = cnv_strarr_long (argc, argv);
	if (!lval_arr)
		return (-1);
	if (lval_arr[0] > INT_MAX)
		return (return_int_msg ("Too many philosophers", -1, &lval_arr));
	mysettings->n_ph = (int) lval_arr[0];
	mysettings->z_die = lval_arr[1] * 1000;
	mysettings->z_eat = lval_arr[2] * 1000;
	mysettings->z_sleep = lval_arr[3] * 1000;
	if (argc == 6)
	{
		if (lval_arr[4] > INT_MAX)
			return (return_int_msg ("eat count is too large", -1, &lval_arr));
		mysettings->n_eat = (int) lval_arr[4];
	}
	free (lval_arr);
	return (value_checks (mysettings, argc));
}

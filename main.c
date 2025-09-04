#include "philo.h"



int return_int_msg(char *str, int val)
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
	return (val);
}


int value_checks(t_settings *mysettings, int extra)
{
	if (mysettings->n_ph <= 0
		|| mysettings->z_die <= 0
		|| mysettings->z_eat <= 0
		|| mysettings->z_sleep <= 0)
		return (return_int_msg ("Values can not be less than 1", -1));
	if (extra == 1 && mysettings->n_eat <= 0)
		return (return_int_msg ("Values can not be less than 1", -1));
	return (1);
}

int	read_settings(t_settings *mysettings, char **argv)
{
	int		extra;
	long	lval;

	extra = 0;
	lval = cnv_atol (argv[1]);
	if (lval > INT_MAX)
		return (return_int_msg ("phil count is too large", -1));
	mysettings->n_ph = (int) lval;
	mysettings->z_die = cnv_atol (argv[2]);
	mysettings->z_eat = cnv_atol (argv[3]);
	mysettings->z_sleep = cnv_atol (argv[4]);
	if (argv[5])
	{
		lval = cnv_atol (argv[5]);
		if (lval > INT_MAX)
			return (return_int_msg ("eat count is too large", -1));
		mysettings->n_eat = (int) lval;
		extra = 1;
	}
	return (value_checks (mysettings, extra));
}

int	main(int argc, char **argv)
{
	t_settings	mysettings;

	// if number of arguments is less than 4 return
	if (argc < 5)
		return (-1);

	// store values in settings
	if (read_settings (&mysettings, argv) != 1)
		return (-1);


	// test
	printf ("n_ph = %d\n", mysettings.n_ph);
	printf ("z_die = %ld\n", mysettings.z_die);
	printf ("z_eat = %ld\n", mysettings.z_eat);
	printf ("z_sleep= %ld \n", mysettings.z_sleep);
	printf ("n_eat = %d\n", mysettings.n_eat);





}
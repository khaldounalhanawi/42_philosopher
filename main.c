#include "philo.h"


void initiate_ph_arr(t_phil *arr_ph, int count)
{
	int	i;
	t_phil ph;

	i = 0;
	while (i < count)
	{
		ph.name = i;
		ph.fork = 0;
		ph.dead = 0;
		arr_ph[i] = ph;
		i ++;
	}
}

int	spawn(t_phil *arr_ph, int count)
{
	int	timer;
	int	i;

	i = 0;
	while (1)
	{
		timer += ()


	}


}

int	main(int argc, char **argv)
{
	t_settings	mysettings;
	t_phil		*arr_ph;

	// if number of arguments is less than 4 return
	if (argc != 5 && argc != 6)
		return (return_int_msg ("Invalid number of arguments", -1, NULL));

	// store values in settings
	if (read_settings (&mysettings, argc, argv) != 1)
		return (-2);

	// create philosophers: malloc memory for count
	arr_ph = malloc (sizeof (t_phil) * mysettings.n_ph);
	if (!arr_ph)
		return (return_int_msg ("failed to create philosophers", -3, NULL));

	// initiate philosophers
	initiate_ph_arr (arr_ph, mysettings.n_ph);

	// create threads?
	// start_thread ();

	// function to start philo
	spawn (arr_ph, argc - 1);










	// test
	printf ("n_ph = %d\n", mysettings.n_ph);
	printf ("z_die = %ld\n", mysettings.z_die);
	printf ("z_eat = %ld\n", mysettings.z_eat);
	printf ("z_sleep= %ld \n", mysettings.z_sleep);
	if (argc == 6)
		printf ("n_eat = %d\n", mysettings.n_eat);




	//

	free (arr_ph);
}


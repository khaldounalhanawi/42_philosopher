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

int	mcs_reset(long *start)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	*start = (time.tv_sec + (time.tv_usec / 1000000)) * 1000;
	return (1);
}

int	spawn(t_settings mysettings, t_phil *arr_ph, long start)
{
	long	time;
	long	now;

	time = 0;
	while (time <= mysettings.z_die)
	{
		mcs_reset (&now);
		time = now - start;
		if (time == 0)
			printf ("time %ld thinking! \n", time);
		usleep (100);

	}
	mcs_reset (&now);
	printf ("done thinking at %ld\n", now - start);
	// print time stamp

	
	// while check forks
		// eating 
			// print time stamp 
			// reset deadline 
			// when eating is done break while

	// while not forks
		// thinking
		// watch timer for dead
		// if dead return


	
	// sleeping
		// start time again?
	printf ("for no warning %d", arr_ph->dead);
	return (1);

}


// number of philosophers
// time to die
// time to eat
// time to sleep
// number of eats must

int	main(int argc, char **argv)
{
	t_settings		mysettings;
	t_phil			*arr_ph;
	long			start;

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

	// start timer
	mcs_reset (&start);

	// function to start philo
	spawn (mysettings, arr_ph, start);










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


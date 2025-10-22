#include "philo.h"

int	main(int argc, char **argv)
{
	t_settings	mysettings;

	if (argc != 5 && argc != 6)
		return (return_int_msg ("Invalid number of arguments", -1, NULL));
	if (read_settings (&mysettings, argc, argv) != 1)
		return (-2);
	if (init_settings (&mysettings) != 1)
		return (-3);
	if (simulate (&mysettings) == -1)
		return (-4);

	// no leaks
	// clean (&mysettings);

}


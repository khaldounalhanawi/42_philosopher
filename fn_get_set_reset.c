#include "philo.h"

int	get_int_mtx(t_mutex *m1, int *read, int *value)
{
	if (!m1)
	{
		printf ("@get_int_mtx: mutex is Null\n");
		return (-1);
	}
	if (pthread_mutex_lock (m1) != 0)
	{
		printf ("@get_int_mtx: couldn't lock mutex\n");
		return (-1);
	}
	*value = *read;
	if (pthread_mutex_unlock (m1) != 0)
	{
		printf ("@get_int_mtx: couldn't unlock mutex\n");
		return (-1);
	}
	return (1);
}

int	set_int_mtx(t_mutex *m1, int *read, int value)
{
	if (pthread_mutex_lock (m1) != 0)
		return (-1);
	*read = value;
	if (pthread_mutex_unlock (m1) != 0)
		return (-1);
	return (1);
}
/*	clean	*/

int	reset_microsecond(unsigned long long *start)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	*start = (unsigned long long) (time.tv_sec * 1000000 + time.tv_usec);
	return (1);
}

int	get_long_mtx(t_mutex *m1, unsigned long long *read, unsigned long long *value)
{
	if (!m1)
		printf ("bad m1 mutex\n");
	if (pthread_mutex_lock (m1) != 0)
		return (-1);
	// printf ("good so far\n");
	*value = *read;
	if (pthread_mutex_unlock (m1) != 0)
		return (-1);	
	return (1);
}
/*	clean	*/

int incriment_int_mtx(t_mutex *mtx, int *value)
{
	if (pthread_mutex_lock(mtx) != 0)
		return -1;
	(*value)++;
	if (pthread_mutex_unlock(mtx) != 0)
		return -1;
	return 1;
}
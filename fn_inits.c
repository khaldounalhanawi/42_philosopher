#include "philo.h"

//	return : 1	on success | -1	on failure
int	fork_create(t_fork *myfork)
{
	if (pthread_mutex_init (&myfork->fork, NULL) != 0)
		return (return_int_msg("failed to initiate fork\n", -1, NULL));
	return (1);
}
/*	Mutex	pthread_mutex_t	@fork_create*/

//	return : 1	on success | -1	on failure
int	init_forks(t_settings *mysettings)
{
	int	i;

	i = 0 ;
	while (i < mysettings->n_ph)
	{
		mysettings->arr_forks[i].fork_id = i;
		if (fork_create (&mysettings->arr_forks[i]) == -1)
			return (-1);
		i ++;
	}
	return (1);
}
/*	Mutex	pthread_mutex_t	@fork_create*/

void	forks_assign(t_settings *mysettings, int pos)
{
	t_phil	*myphil;
	int		count;

	myphil = &mysettings->arr_phil[pos];
	count = mysettings->n_ph;
	
	// Standard assignment
	myphil->left_fork = &mysettings->arr_forks[pos];
	myphil->right_fork = &mysettings->arr_forks[(pos + 1) % count];
	
	// Deadlock prevention: last philosopher picks up forks in reverse order
	// if (pos == count - 1) {
	// 	myphil->left_fork = &mysettings->arr_forks[(pos + 1) % count];
	// 	myphil->right_fork = &mysettings->arr_forks[pos];
	// }
}
/*	clean	*/

//	return : 1	on success | -1	on failure
int init_phils(t_settings *mysettings)
{
	int	i;

	i = 0;
	while (i < mysettings->n_ph)
	{
		mysettings->arr_phil[i].mysettings = mysettings;
		mysettings->arr_phil[i].id = i;
		mysettings->arr_phil[i].meals_counter = 0;
		mysettings->arr_phil[i].full = 0;
		mysettings->arr_phil[i].last_meal_time = 0;
		forks_assign (mysettings, i);
		i ++;
	}
	return (1);
}
/*	clean	*/

//	return : 1	on success | -1	on failure
int	init_settings(t_settings *mysettings)
{

	mysettings->arr_forks = malloc (sizeof (t_fork) * mysettings->n_ph);
	if (!mysettings->arr_forks)
		return (-1);
	mysettings->arr_phil = malloc (sizeof (t_phil) * mysettings->n_ph);
	if (!mysettings->arr_phil)
		return (-1);
	if (init_forks (mysettings) != 1)
		return (-1);
	if (init_phils (mysettings) != 1)
		return (-1);
	mysettings->start_sim = 0;
	mysettings->end = malloc (sizeof (int));
	*(mysettings->end) = 0;
	mysettings->all_threads_ready = 0;
	if (pthread_mutex_init (&(mysettings->mtx_ready_to_start), NULL) != 0)
		return (-1);
	if (pthread_mutex_init (&(mysettings->mtx_end), NULL) != 0)
		return (-1);
	if (pthread_mutex_init (&(mysettings->mtx_print), NULL) != 0)
		return (-1);
	if (pthread_mutex_init (&(mysettings->mtx_time), NULL) != 0)
		return (-1);
	if (pthread_mutex_init (&(mysettings->mtx_full_philosophers), NULL) != 0)
		return (-1);
	if (pthread_mutex_init (&(mysettings->mtx_last_eat_time), NULL) != 0)
		return (-1);
	return (1);
}
/*	t_fork	malloc
 *	t_phil	malloc
 *	Mutex	pthread_mutex_t	@init_forks.fork_create */


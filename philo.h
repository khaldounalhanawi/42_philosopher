# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
#include <stdlib.h>
# include <limits.h>
# include <pthread.h>
#include <time.h>
#include <sys/time.h>

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage:
**     printf(R "This is red text." RST);
**     printf(B "This is blue text." RST);
** Remember to use RST to reset the color after setting it.
*/
#define RST "\033[0m"    /* Reset to default color */
#define RED "\033[1;31m" /* Bold Red */
#define G   "\033[1;32m" /* Bold Green */
#define Y   "\033[1;33m" /* Bold Yellow */
#define B   "\033[1;34m" /* Bold Blue */
#define M   "\033[1;35m" /* Bold Magenta */
#define C   "\033[1;36m" /* Bold Cyan */
#define W   "\033[1;37m" /* Bold White */


typedef pthread_mutex_t t_mutex;
typedef struct s_settings t_settings;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_phil
{
	int					id;
	long				meals_counter;
	int					full;
	unsigned long long	last_meal_time;
	t_fork				*right_fork;
	t_fork				*left_fork;
	pthread_t			thread;
	t_settings			*mysettings;
}	t_phil;

struct s_settings
{
	int					n_ph;
	unsigned long long	z_die;
	unsigned long long	z_eat;
	unsigned long long	z_sleep;
	int					n_eat;
	unsigned long long	start_sim;
	int					*end;
	int					all_threads_ready;
	int					full_philosophers_count;
	t_mutex				mtx_time;
	t_mutex				mtx_full_philosophers;
	t_mutex				mtx_ready_to_start;
	t_mutex				mtx_end;
	t_mutex				mtx_last_eat_time;
	t_mutex				mtx_print;
	t_fork				*arr_forks;
	t_phil				*arr_phil;
	pthread_t			monitor;
};
// number die eat sleep count
typedef struct s_args
{
	t_settings			mysettings;
	t_phil				*arr_ph;
	unsigned long long	start;
	int					pos;
}	t_args;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FORK1,
	FORK2
}	t_state;



/*fn_convertors*/
long long	cnv_atol(const char *str);
long		*cnv_strarr_long(int argc, char **argv);
int			fn_isdigit(char *str);

/*fn_return_functions*/
int			return_int_msg(char *str, int val, long **lval_arr);
void		*return_null_str(char *str);
int			print_status(t_state state, t_phil *phil);

/*fn_read_functions*/
int			read_settings(t_settings *mysettings, int argc, char **argv);
/*fn_inits*/
int			init_settings(t_settings *mysettings);
/*fn_sleep_improve*/
int			improved_usleep(unsigned long long input, t_settings *mysettings);

int			simulation_finished(t_settings *mysettings);

/*fn_get_set_reset*/
int			get_int_mtx(t_mutex *m1, int *read, int *value);
int			set_int_mtx(t_mutex *m1, int *read, int value);
int			reset_microsecond(unsigned long long *start);
int			get_long_mtx(t_mutex *m1, unsigned long long *read, unsigned long long *value);

int			simulate(t_settings *mysettings);

void		*dinner_sim(void *data);
void		*death_monitor(void *p);
int			simulation_finished(t_settings *mysettings);
int			wait_for_all_start(t_settings *mysettings);

int			incriment_int_mtx(t_mutex *mtx, int *value);
int			eat_action(t_phil *phil);
int			think_action(t_phil *philosopher);

// fn_inits_II.c
int			init_forks(t_settings *mysettings);
int			init_phils(t_settings *mysettings);
int			init_mutexes(t_settings *mysettings);

// fn_cleanup.c
void		clear_mysettings(t_settings	*mysettings);
void		clear_forks(t_settings	*mysettings, int pos);


# endif

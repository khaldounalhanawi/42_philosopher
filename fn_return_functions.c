#include "philo.h"

void put_str(char *str)
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
}

int return_int_msg(char *str, int val, long **lval_arr)
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
	if (lval_arr)
		free (*lval_arr);
	return (val);
}

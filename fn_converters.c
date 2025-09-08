#include "philo.h"

long long	cnv_atol(const char *str)
{
	long long	val;
	long long	sign;

	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	val = 0;
	while (*str >= '0' && *str <= '9')
	{
		val = (val * 10) + (*str - '0');
		str++;
	}
	return (val * sign);
}

long	*cnv_strarr_long(int argc, char **argv)
{
	long long	llval;
	long		*arr;
	int			i;

	i = 0;
	arr = malloc (sizeof (long *) * argc - 1);
	if (!arr)
		return (NULL);
	while (i + 1 < argc)
	{
		llval = cnv_atol(argv[i + 1]);
		if (llval > LONG_MAX)	
		{
			free (arr);
			put_str ("long value too large");
			return (NULL);
		}
		arr[i] = (long) (llval);
		i++;
	}
	return (arr);
}
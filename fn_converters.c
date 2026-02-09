/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_converters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:40:10 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/09 11:40:05 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fn_isdigit(char *str)
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

long	*cnv_strarr_long(int argc, char **argv)
{
	long long	llval;
	long		*arr;
	int			i;

	if (!fn_isdigit_arr (argc, argv))
		return (return_null_str ("Bad input: Input not digits\n"));
	i = 0;
	arr = malloc (sizeof (long) * (argc - 1));
	if (!arr)
		return (return_null_str("fialed to malloc long array\n"));
	while (i + 1 < argc)
	{
		llval = cnv_atol(argv[i + 1]);
		if (llval > LONG_MAX)
		{
			free (arr);
			return (return_null_str("long value too large\n"));
		}
		arr[i] = (long)(llval);
		i++;
	}
	return (arr);
}

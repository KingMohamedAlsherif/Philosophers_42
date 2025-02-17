/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:16:42 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/17 20:04:01 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_max_min(char *str)
{
	int			si;
	long long	res;

	res = 0;
	si = 1;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			si = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (si == 1 && res > INT_MAX)
			return (0);
		else if (si == -1 && (-res) < INT_MIN)
			return (0);
		str++;
	}
	return (1);
}

int	check_philo_args(char **av)
{
	int	i;

	i = 1;
	if (ft_atol(av[i]) > 200 || ft_atol(av[i]) < 1)
		return (0);
	while (av[++i])
	{
		if (!check_max_min(av[i]) || ft_atol(av[i]) < 1)
			return (0);
	}
	return (1);
}

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

const char	*valid_input(const char *str)
{
	int			len;
	const char	*num;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		erroring("INPUT ONLY POSITIVE NUMBERS!");
	while (!is_digit(*str))
		erroring("INPUT ONLY DIGITS!");
	num = str;
	while (is_digit(*str))
	{
		str++;
		len++;
	}
	if (len > 10)
		erroring("INT_MAX IS THE LIMIT!");
	return (num);
}

void	erroring(char *str)
{
	write(2, str, strlen(str));
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:00:18 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/17 19:57:59 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *num)
{
	long	ret;

	ret = 0;
	num = valid_input(num);
	while (is_digit(*num))
		ret = (ret * 10) + *num++ - 48;
	if (ret > INT_MAX)
		erroring("TRY NUMBERS SMALLER THAN THE INT MAX!!!");
	return (ret);
}

int	printing(int philo_id, char *str, t_philo *philo)
{
	if (philo->print == NULL)
	{
		printf("Error: print_lock is NULL\n");
		return (1);
	}
	pthread_mutex_lock(philo->print);
	if (!check_dead_st(philo))
		printf("%zu %d %s\n",
			get_time() - philo->times.sim_start, philo_id, str);
	pthread_mutex_unlock(philo->print);
	return (0);
}

size_t	time_stamp(size_t sim_start)
{
	return (get_time() - sim_start);
}

int	wait_time(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (check_dead_st(philo))
			return (0);
		usleep(500);
	}
	return (0);
}

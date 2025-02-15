/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:16:42 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/13 09:24:30 by malsheri         ###   ########.fr       */
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
		else if ((si == -1) && (-res < INT_MIN))
			return (0);
		str++;
	}
	return (1);
}
int check_philo_args(char   **av)
{
    int i;

    i = 1;
    if (ft_atol(av[i]) > 200 || ft_atol(av[i]) < 1)
        return (0);
    while(av[++i])
    {
        if (!check_max_min(av[i]) || ft_atol(av[i]) < 1)
            return (0);
    }
    return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:01:37 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/17 19:59:44 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philos[200];
	t_mtx	forks_mtx[200];
	int		forks[200];

	if (ac < 5 || ac > 6)
		erroring("Error: Invalid number of arguments\n");
	if (!check_philo_args(av))
		erroring("Error: Invalid philosopher arguments\n");
	if (!init_data(&data, av, philos, ac))
		erroring("Error: Failed to initialize philosophers\n");
	if (!init_forks(forks, forks_mtx, data.philo_num))
		erroring("Error: Failed to initialize threads\n");
	init_philos(&data, philos, forks, forks_mtx);
	if (!init_th(philos, &data))
	{
		des_mtx(&data, forks_mtx, NULL);
		erroring("Error: Failed to join threads\n");
	}
	return (0);
}

void	des_mtx(t_data *data, t_mtx *forks, char *str)
{
	int	i;

	i = -1;
	if (str)
		erroring(str);
	while (++i < data->philo_num)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_status);
	pthread_mutex_destroy(&data->meal_count_lock);
}

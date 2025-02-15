/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:01:37 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/13 10:22:14 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int     main(int    ac, char    **av)
{
    t_data  data;
    t_philo philos[200];
    t_mtx forks_mtx[200];
    int         forks[200];

    if (ac < 5 || ac > 6)
        erroring("Error: Invalid number of arguments\n");
    if (!check_philo_args(ac, av))
        erroring("Error: Invalid philosopher arguments\n");
    if (!init_data(&data))
        erroring("Error: Failed to initialize philosophers\n");
    if (!init_forks(&data)) // not implemented
        erroring("Error: Failed to initialize threads\n");
    init_philos(&data, philos, forks, forks_mtx); // not implemented
    if (join_threads(&data)) // not implemented
        erroring("Error: Failed to join threads\n");
    return (0);
}
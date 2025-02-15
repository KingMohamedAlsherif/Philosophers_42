/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:50:05 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/14 10:54:11 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void     init_th(t_philo *philos, t_data *data)
{
        int i;
        
        if (pthread_create(&data->monitor, NULL, &monitor_thread, data) != 0)
            erroring("Error creating monitor thread");
        i = -1;
        while (++i, i < data->philo_num)
        {
            if (pthread_create(&philos[i].thread, NULL, &philo_thread, &philos[i]) != 0)
                erroring("Error creating philosopher thread");
        }
        if (pthread_join(data->monitor, NULL) != 0)
            erroring("Error joining monitor thread");
        i = -1;
        while (++i, i < data->philo_num)
        {
            if (pthread_join(philos[i].thread, NULL) != 0)
                erroring("Error joining philosopher thread");
        }
}

int init_data(t_data *data, char    **av, t_philo   *philos, int    ac)
{
    int i;

    i = -1;
    data->philo_num = ft_atol(av[1]);
    while (++i < data->philo_num)
    {
        philos[i].id = i + 1;
        philos[i].times.to_die = ft_atol(av[2]);
        philos[i].times.to_eat = ft_atol(av[3]);
        philos[i].times.to_sleep = ft_atol(av[4]);
        philos[i].eating = 0;
        philos[i].meals_eaten = 0;
    }
    if (ac == 6)
        data->meal_num = ft_atol(av[5]);
    else
        data->meal_num = -1;
    data->philos = philos;
    data->is_dead = 0;
    if (pthread_mutex_init(&data->print, NULL) 
        || pthread_mutex_init(&data->dead_status, NULL) 
        || pthread_mutex_init(&data->meal_count_lock, NULL))
        return (0);
    return (1);
}

int     init_forks(int  *forks, t_mtx  *forks_mtx, int    philo_num)
{
    int i;

    i = -1;
    while (philo_num > ++i)
    {
        forks[i] = 1;
        if (pthread_mutex_init(&forks_mtx[i], NULL))
            return (0);
    }
    return (1);
}

void    init_philos(t_data  *data, t_philo  *philos, int    *forks, t_mtx   *forks_mtx)
{
    int i;

    i = -1;
    while(++i < data->philo_num)
    {
        philos[i].total_philo = data->philo_num;
        philos[i].sync.dead = &data->is_dead;
        philos[i].times.last_meal = get_time();
        philos[i].times.sim_start = get_time();
        philos[i].print = &data->print;
        philos[i].sync.dead = &data->dead_status;
        philos[i].sync.meal_lock = &data->meal_count_lock;
        philos[i].forks.right = &forks[i];
        if ((data->philo_num - 1) == i)
            philos[i].forks.left = &forks[0];
        else
            philos[i].forks.left = &forks[i + 1];
        philos[i].forks.right_lock = &forks_mtx[i];
        if ((data->philo_num - 1) == i)
            philos[i].forks.left_lock = &forks_mtx[0];
        else
            philos[i].forks.left_lock = &forks_mtx[i + 1];
    }
}


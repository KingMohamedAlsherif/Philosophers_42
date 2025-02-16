/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:14:31 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/15 10:42:30 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *monitor_thread(void *a)
{
    t_data *data;
    t_philo *philos;
    
    data = (t_data *)a;
    philos = data->philos;
    while(1)
    {
        usleep(100);
        if (check_die(philos, data) || check_eat_time(philos, data))
            return (NULL);
    }
    return (NULL);
}

int check_die(t_philo   *philos, t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_num)
    {
        pthread_mutex_lock(philos[i].sync.meal_lock);
        if ((get_time() - philos[i].times.last_meal) > philos[i].times.to_die 
            && !philos[i].eating)
        {
            printing(philos[i].id, "died", philos);
            pthread_mutex_lock(philos[i].sync.dead_st);
            *philos[i].sync.dead = 1;
            pthread_mutex_unlock(philos[i].sync.dead_st);
            return (pthread_mutex_unlock(philos[i].sync.meal_lock), 1);
        }
        pthread_mutex_unlock(philos[i].sync.meal_lock);
    }
    return (0);
}

int check_eat_time(t_philo *philos, t_data *data)
{
    int i;
    int all;

    i = -1;
    all = 0;
    if (data->meal_num == -1)
        return (0);
    while (data->philo_num > ++i)
    {
        pthread_mutex_lock(philos[i].sync.meal_lock);
        if (philos[i].meals_eaten >= data->meal_num)
            all++;
        pthread_mutex_unlock(philos[i].sync.meal_lock);
    }
    if (all == data->philo_num)
    {
        pthread_mutex_lock(&data->dead_status);
        data->is_dead = 1;
        pthread_mutex_unlock(&data->dead_status);
        return (1);
    }
    return (0);
}

int     check_dead_st(t_philo   *philo)
{
    pthread_mutex_lock(philo->sync.dead_st);
    if (*philo->sync.dead)
    {
        pthread_mutex_unlock(philo->sync.dead_st);
        return (1);
    }
    pthread_mutex_unlock(philo->sync.dead_st);
    return (0);
}

size_t  get_time(void)
{
    struct timeval  t;
    size_t          ret;
    if (gettimeofday(&t, NULL) == -1)
        erroring("Error getting time\n");
    ret = (t.tv_sec * 1000) + (t.tv_usec / 1000);
    return (ret);
}

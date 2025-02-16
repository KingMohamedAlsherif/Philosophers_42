/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 05:53:39 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/16 07:56:11 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_thread(void   *a)
{
    t_philo *philo;
    
    philo = (t_philo *)a;
    if (philo->total_philo == 1)
    {
        printing(philo->id, "has taken a fork", philo);
        wait_time(philo->times.to_die, philo);
        return (NULL);
    }
    if (philo->id % 2 == 0)
        wait_time(1, philo);
    while (!check_dead_st(philo))
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return (NULL);
}

void    mtx_order_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->forks.right_lock);
        pthread_mutex_lock(philo->forks.left_lock);
    }
    else
    {
        pthread_mutex_lock(philo->forks.left_lock);
        pthread_mutex_lock(philo->forks.right_lock);
    }
}


void    eating(t_philo *philo)
{
    mtx_order_forks(philo);
    pthread_mutex_lock(philo->sync.meal_lock);
    philo->times.last_meal = get_time();
    philo->eating = 1;
    philo->meals_eaten++;
	pthread_mutex_unlock(philo->sync.meal_lock);
	printing(philo->id, "has taken a fork", philo);
	printing(philo->id, "has taken another fork", philo);
	printing(philo->id, "is eating", philo);
    *(philo->forks.right) = 0;
    *(philo->forks.left) = 0;
    wait_time(philo->times.to_eat, philo);
    pthread_mutex_lock(philo->sync.meal_lock);
    philo->eating = 0;
    pthread_mutex_unlock(philo->sync.meal_lock);
    *(philo->forks.right) = 1;
    *(philo->forks.left) = 1;
    pthread_mutex_unlock(philo->forks.right_lock);
    pthread_mutex_unlock(philo->forks.left_lock);
}

void    sleeping(t_philo *philo)
{
    printing(philo->id, "is sleeping", philo);
    wait_time(philo->times.to_sleep, philo);
}

void    thinking(t_philo *philo)
{
    printing(philo->id, "is thinking", philo);
}
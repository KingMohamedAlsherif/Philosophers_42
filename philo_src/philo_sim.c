/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 05:53:39 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/15 09:32:54 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_thread(void   *a)
{
    t_philo *philo;
    
    philo = (t_philo *)a;
    if (philo->total_philo == 1)
    {
        printing(philo->id, "has taken a fork", philo);
        wait_time(philo->times.to_die, philo);
        return ;
    }
    if (philo->id % 2 == 0)
        wait_time(1, philo);
    while (!check_dead_st(philo))
    {
        eating(philo); // not implemented
        sleeping(philo); // not implemented
        thinking(philo); // not implemented
    }
    return ;
}

void    mtx_fork_order(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->forks.right_lock);
        pthread_mutex_lock(&philo->forks.left_lock);
    }
    else
    {
        pthread_mutex_lock(&philo->forks.left_lock);
        pthread_mutex_lock(&philo->forks.right_lock);
    }
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:14:31 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/14 11:55:22 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    monitor_thread(void *a)
{
    t_data *data;
    t_philo *philos;
    
    data = (t_data *)a;
    philos = data->philos;
    while(1)
    {
        usleep(100);
        if (check_die(philos, data) || check_eat_time(philos, data))
            return ;
    }
    return ;
}

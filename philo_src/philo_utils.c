/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:00:18 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/15 09:17:01 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    erroring(char *str)
{
    write(2, str, strlen(str));
    exit(1);
}

static is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}



long    ft_atol(const   char    *num)
{
    long    ret;

    ret = 0;
    num = valid_input(num);
    while(is_digit(*num))
        ret = (ret * 10) + *num++ - 48;
    if (ret > INT_MAX)
        erroring("TRY NUMBERS SMALLER THAN THE INT MAX!!!");
    return (ret);
}

void    printing(int philo_id, char *str, t_philo *philo)
{
    pthread_mutex_lock(philo->sync.print_lock);
    if (!check_dead_st(philo))
        printf("%zu %d %s\n", get_time() - philo->times.sim_start, philo_id, str);
    pthread_mutex_unlock(philo->sync.print_lock);
}

size_t  time_stamp(size_t sim_start)
{
    size_t ret;
    ret = get_time() - sim_start;
    return (ret);
}

int wait_time(size_t time, t_philo *philo)
{
    size_t start;

    start = get_time();
    while (get_time() - start < time)
    {
        if (check_dead_st(philo))
            return (0);
        usleep(500);
    }
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

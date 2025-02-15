/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:00:18 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/13 09:04:17 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    erroring(char *str)
{
    write(2, str, strlen(str));
    exit(1);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:55:13 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/17 19:57:17 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_forks
{
	int				*left;
	int				*right;
	pthread_mutex_t	*left_lock;
	pthread_mutex_t	*right_lock;
}					t_forks;

typedef struct s_timing
{
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
	size_t			last_meal;
	size_t			sim_start;
}					t_timing;

typedef struct s_sync
{
	int				*dead;
	int				*eating;
	t_mtx			*dead_st;
	t_mtx			*meal_lock;
}					t_sync;

typedef struct s_philo
{
	int				id;
	int				total_philo;
	int				eating;
	int				meals_eaten;
	t_mtx			*print;
	pthread_t		thread;
	t_forks			forks;
	t_timing		times;
	t_sync			sync;
}					t_philo;

typedef struct s_data
{
	int				philo_num;
	int				meal_num;
	int				is_dead;
	t_philo			*philos;
	t_mtx			print;
	t_mtx			dead_status;
	t_mtx			meal_count_lock;
	pthread_t		monitor;
}					t_data;

// UTIL functions
size_t		get_time(void);
long		ft_atol(const char *num);
int			printing(int philo_id, char *str, t_philo *philo);
size_t		time_stamp(size_t sim_start);
int			wait_time(size_t time, t_philo *philo);

// INIT functions
int			init_th(t_philo *philos, t_data *data);
int			init_data(t_data *data, char **av, t_philo *philos, int ac);
int			init_forks(int *forks, t_mtx *forks_mtx, int philo_num);
void		init_philos(t_data *data, t_philo *philos,
				int *forks, t_mtx *forks_mtx);

// Monitor functions
void		*monitor_thread(void *a);
int			check_die(t_philo *philos, t_data *data);
int			check_eat_time(t_philo *philos, t_data *data);

// Simulation functions
int			check_dead_st(t_philo *philo);
void		*philo_thread(void *a);
void		mtx_order_forks(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
int			check_dead_st(t_philo *philo);

// Parsing functions
const char	*valid_input(const char *str);
int			check_max_min(char *str);
int			check_philo_args(char **av);
void		erroring(char *str);
void		des_mtx(t_data *data, t_mtx *forks, char *str);
int			is_digit(char c);

#endif

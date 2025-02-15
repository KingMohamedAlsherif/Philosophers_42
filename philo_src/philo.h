#ifndef PHILO_H
#define  PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>



typedef pthread_mutex_t t_mtx;

typedef struct s_forks
{
	int				*left;
	int				*right;
	pthread_mutex_t	*left_lock;
	pthread_mutex_t	*right_lock;
}				t_forks;

typedef struct s_timing
{
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
	size_t			last_meal;
	size_t			sim_start;
}				t_timing;

typedef struct s_sync
{
	int				*dead;
    int             *eating;
	t_mtx			*print_lock;
	t_mtx			*dead_st;
	t_mtx			*meal_lock;
}				t_sync;

typedef struct s_philo
{
	int				id;
	int				total_philo;
	int				eating;
	int				meals_eaten;
    t_mtx           *print;
	pthread_t		thread;
	t_forks			forks;
	t_timing		times;
	t_sync			sync;
}				t_philo;

typedef struct s_data
{
	int				philo_num;            // Number of philosophers
	int				meal_num;             // Number of meals required before stopping
	int				is_dead;              // Flag to indicate if any philosopher has died
	t_philo 	    *philos;              // Array of philosophers
	t_mtx			print;                // Mutex for printing messages
	t_mtx			dead_status;          // Mutex for checking dead status
	t_mtx			meal_count_lock;      // Mutex for updating meal counts
	pthread_t		monitor;               // Thread to monitor philosophers' status
}					t_data;


long    ft_atol(const   char    *num);
void    erroring(char *str);
int     check_max_min(char *str);
int     check_philo_args(int ac, char **av);
int     init_threads(t_data *data);
void    monitor_thread(void *a);	
int     check_dead_st(t_philo   *philo);
const   char    *valid_input(const  char    *str);
void    philo_thread(void   *a);
void    printing(int philo_id, char *str, t_philo *philo);
size_t  time_stamp(size_t sim_start);
int wait_time(size_t time, t_philo *philo);
size_t  get_time(void);




#endif
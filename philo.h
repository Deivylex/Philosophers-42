#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# define ms 1000

typedef struct s_table	t_table;

typedef struct s_philo
{

    pthread_t		thread;
    int				id;
	int				n_meals;
	long			last_meal;
	int				forks[2];
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	time_lock;
    t_table        *table;
} t_philo;

typedef struct s_table
{
    long            philo_nbrs;
    long            time_die;
    long            time_eat;
    long            time_sleep;
    long            max_meals;
    long            start_time;
    t_philo         **philo;
    pthread_mutex_t dead_lock;
	pthread_mutex_t	*forks_lock;
	pthread_t       watch;
}	t_table;


void    philo_error(const char *str);
void    make_arguments(char **av, t_table *content);
void    init_table(t_table *table);
void    error_cleaning (t_table *table, char type);
void	ft_putstr_fd(char *s, int fd);

#endif
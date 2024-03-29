#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# define ms 1000

typedef struct s_data
{
    long    philo_nbrs;
    long    time_die;
    long    time_eat;
    long    time_sleep;
    long    max_meals;
}	t_data;

typedef struct {
    int index;
    t_data *content;
} thread_args;

void    philo_error(const char *str);
void    make_arguments(char **av, t_data *content);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:46:34 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/03 19:58:18 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# define MS 1000
# define MUTEX_FORK 1
# define MUTEX_MEAL 2
# define MUTEX_TIME 3

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	int				forks[2];
	int				philo_died;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	time_lock;
	t_table			*table;
}			t_philo;

typedef struct s_table
{
	long			philo_nbrs;
	int				exit_status;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			max_meals;
	long			start_time;
	int				dead;
	t_philo			**philo;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks_lock;
}	t_table;

void	philo_error(t_table *table, char *str);
void	make_arguments(char **av, t_table *content);
void	init_table(t_table *table);
void	error_cleaning(t_table *table, char type);
void	ft_putstr_fd(char *s, int fd);
void	join_thread(t_table *table, int i);
void	error_mutex(t_table *table, int type, int i);
//times
long	get_time(void);
void	precise_sleep_ms(long time, t_philo *philo);
//philo simulation
void	*philo_simulation(void *arg);
int		philo_dead(t_philo *philo);

#endif

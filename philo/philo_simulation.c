/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:20:17 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/03 17:59:07 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	printing_logs(t_philo *philo, char c)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead == 0)
	{
		if (c == 'f')
			printf("%ld %d has taken a fork\n",
				(get_time() - philo->table->start_time), philo->id);
		if (c == 'e')
			printf("%ld %d is eating\n",
				(get_time() - philo->table->start_time), philo->id);
		if (c == 's')
			printf("%ld %d is sleping\n",
				(get_time() - philo->table->start_time), philo->id);
		if (c == 't')
			printf("%ld %d is thinking\n",
				(get_time() - philo->table->start_time), philo->id);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
}

static void	eating_step(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks_lock[philo->forks[0]]);
		printing_logs(philo, 'f');
	}
	pthread_mutex_lock(&philo->table->forks_lock[philo->forks[1]]);
	printing_logs(philo, 'f');
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->table->forks_lock[philo->forks[0]]);
		printing_logs(philo, 'f');
	}
	printing_logs(philo, 'e');
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->time_lock);
	precise_sleep_ms(philo->table->time_eat, philo);
	pthread_mutex_unlock(&philo->table->forks_lock[philo->forks[0]]);
	pthread_mutex_unlock(&philo->table->forks_lock[philo->forks[1]]);
	pthread_mutex_lock(&philo->meal_lock);
	philo->n_meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	philo_dead(philo);
	printing_logs(philo, 's');
	precise_sleep_ms(philo->table->time_sleep, philo);
}

static void	thinking_step(t_philo *philo)
{
	printing_logs(philo, 't');
	pthread_mutex_lock(&philo->time_lock);
	precise_sleep_ms((philo->table->time_eat * 2)
		- (philo->table->time_eat + philo->table->time_sleep), philo);
	pthread_mutex_unlock(&philo->time_lock);
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_lock[philo->forks[0]]);
	printing_logs(philo, 'f');
	usleep(philo->table->time_die);
	pthread_mutex_lock(&philo->table->dead_lock);
	printf("%ld %d died\n", philo->table->time_die, philo->id);
	philo->table->dead = 1;
	pthread_mutex_unlock(&philo->table->dead_lock);
	pthread_mutex_unlock(&philo->table->forks_lock[philo->forks[0]]);
}

void	*philo_simulation(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->table->time_die == 0)
		return (NULL);
	if (philo->table->philo_nbrs == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->time_lock);
	if (philo->id % 2)
		precise_sleep_ms(philo->table->time_eat, philo);
	while (philo_dead(philo) == 0)
	{
		eating_step(philo);
		thinking_step(philo);
		if (philo->n_meals >= philo->table->max_meals
			&& philo->table->max_meals > 0)
			break ;
	}
	return (NULL);
}

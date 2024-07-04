/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:23:33 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/04 12:15:11 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead == 1)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	if ((get_time() - philo->last_meal) >= philo->table->time_die)
	{
		pthread_mutex_lock(&philo->table->dead_lock);
		printf("%ld %d died\n", philo->table->time_die, philo->id);
		philo->table->dead = 1;
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (1);
	}
	return (0);
}

void	error_mutex(t_table *table, int type, int i)
{
	int	check;

	check = -1;
	if (type == MUTEX_FORK)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&table->forks_lock[i]);
	}
	if (type == MUTEX_MEAL)
	{
		while (++check < table->philo_nbrs)
			pthread_mutex_destroy(&table->forks_lock[i]);
		while (--i >= 0)
			pthread_mutex_destroy(&table->philo[i]->meal_lock);
	}
	if (type == MUTEX_TIME)
	{
		while (++check < table->philo_nbrs)
			pthread_mutex_destroy(&table->forks_lock[i]);
		check = -1;
		while (++check < table->philo_nbrs)
			pthread_mutex_destroy(&table->philo[i]->meal_lock);
		while (--i >= 0)
			pthread_mutex_destroy(&table->philo[i]->time_lock);
	}
}

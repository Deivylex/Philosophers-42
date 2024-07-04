/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:45:33 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/03 19:56:04 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fill_philos(t_table *table)
{
	int	i;

	if (table->exit_status)
		return ;
	i = -1;
	while (++i < table->philo_nbrs)
	{
		table->philo[i]->id = i + 1;
		table->philo[i]->n_meals = 0;
		table->philo[i]->forks[0] = i;
		table->philo[i]->forks[1] = i + 1;
		if (i == table->philo_nbrs - 1)
			table->philo[i]->forks[1] = 0;
		table->philo[i]->table = table;
	}
}

static	void	init_mutex_fork(t_table *table)
{
	int	i;

	if (table->exit_status)
		return ;
	table->forks_lock = malloc(sizeof(pthread_mutex_t) * table->philo_nbrs);
	if (table->forks_lock == NULL)
		error_cleaning(table, 'm');
	i = -1;
	while (++i < table->philo_nbrs)
	{
		if (pthread_mutex_init(&table->forks_lock[i], NULL))
		{
			error_mutex(table, MUTEX_FORK, i);
			error_cleaning(table, 'x');
		}
	}
	if (pthread_mutex_init(&table->dead_lock, NULL))
		return ;
}

static void	init_mutex_check(t_table *table)
{
	int	i;

	if (table->exit_status)
		return ;
	i = -1;
	while (++i < table->philo_nbrs)
	{
		if (pthread_mutex_init(&table->philo[i]->meal_lock, NULL))
		{
			error_mutex(table, MUTEX_MEAL, i);
			error_cleaning(table, 'x');
		}
	}
	i = -1;
	while (++i < table->philo_nbrs)
	{
		if (pthread_mutex_init(&table->philo[i]->time_lock, NULL))
		{
			error_mutex(table, MUTEX_TIME, i);
			error_cleaning(table, 'x');
		}
	}
}

static void	create_threads(t_table *table)
{
	int	i;

	if (table->exit_status)
		return ;
	table->start_time = get_time();
	i = -1;
	while (++i < table->philo_nbrs)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, &philo_simulation,
				table->philo[i]))
		{
			join_thread(table, i);
			error_cleaning(table, 'p');
		}
	}
}

void	init_table(t_table *table)
{
	int	i;

	if (table->exit_status)
		return ;
	table->dead = 0;
	table->philo = malloc(sizeof(t_philo *) * table->philo_nbrs);
	if (table->philo == NULL)
		error_cleaning(table, 'm');
	if (table->exit_status)
		return ;
	i = -1;
	while (++i < table->philo_nbrs)
	{
		table->philo[i] = malloc(sizeof(t_philo));
		if (table->philo[i] == NULL)
			error_cleaning(table, 'm');
	}
	fill_philos(table);
	init_mutex_fork(table);
	init_mutex_check(table);
	create_threads(table);
}

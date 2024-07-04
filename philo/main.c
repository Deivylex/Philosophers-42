/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:45:07 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/04 12:14:11 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_error(t_table *table, char *str)
{
	if (table->exit_status == 0)
	{
		ft_putstr_fd(str, 2);
		table->exit_status = 1;
	}
}

void	join_thread(t_table *table, int lim)
{
	int	i;

	if (table->exit_status)
		return ;
	i = -1;
	while (++i < lim)
	{
		if (pthread_join(table->philo[i]->thread, NULL))
			error_cleaning(table, 'j');
	}
}

void	free_philos(t_table *table)
{
	int	i;

	if (table->exit_status)
		return ;
	i = -1;
	while (++i < table->philo_nbrs)
	{
		pthread_mutex_destroy(&table->forks_lock[i]);
		pthread_mutex_destroy(&table->philo[i]->meal_lock);
		pthread_mutex_destroy(&table->philo[i]->time_lock);
	}
	pthread_mutex_init(&table->dead_lock, NULL);
	free (table->forks_lock);
	i = -1;
	while (++i < table->philo_nbrs && table->philo[i])
		free(table->philo[i]);
	free(table->philo);
}

int	main(int ac, char **av)
{
	t_table	table;

	table.exit_status = 0;
	if (ac < 5)
		philo_error(&table, "Missing arguments\n");
	if (ac > 6)
		philo_error(&table, "Too many arguments\n");
	make_arguments(av, &table);
	init_table(&table);
	join_thread(&table, table.philo_nbrs);
	free_philos(&table);
	error_mutex(&table, MUTEX_FORK, 5);
	return (table.exit_status);
}

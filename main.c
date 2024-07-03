/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:45:07 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/03 16:26:51 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}

void	join_thread(t_table *table, int lim)
{
	int	i;

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

	if (ac < 5)
		philo_error("Missing arguments\n");
	if (ac > 6)
		philo_error("Too many arguments\n");
	make_arguments(av, &table);
	init_table(&table);
	join_thread(&table, table.philo_nbrs);
	free_philos(&table);
}

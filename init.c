/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita@student.hive.fi <dzurita>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:47:01 by dzurita@stu       #+#    #+#             */
/*   Updated: 2024/06/18 17:54:43 by dzurita@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    fill_philos(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_nbrs)
    {
        table->philo[i]->id = i + 1;
        table->philo[i]->n_meals = 0;
        table->philo[i]->forks[0] = i;
        table->philo[i]->forks[1] = i + 1;
        table->philo[i]->table = table;
    }   
}

void    init_mutex_fork(t_table *table)
{
    int i;

    table->forks_lock = malloc(sizeof(pthread_mutex_t) * table->philo_nbrs);
    if (table->forks_lock == NULL)
        error_cleaning(table, 'm');
    i = -1;
    while (++i < table->philo_nbrs)
    {
        if (pthread_mutex_init(&table->forks_lock[i], NULL))
        {
            while (--i > 0)
                pthread_mutex_destroy(&table->forks_lock[i]);
            error_cleaning(table, 'x');
        }
    }   
}
void    init_mutex_check(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_nbrs)
    {
        if (pthread_mutex_init(&table->philo[i]->meal_lock, NULL))
        {
            while (--i > 0)
                pthread_mutex_destroy(&table->philo[i]->meal_lock);
            error_cleaning(table, 'x');
        }
    }
    i = -1;
    while (++i < table->philo_nbrs)
    {
        if (pthread_mutex_init(&table->philo[i]->time_lock, NULL))
        {
            while (--i > 0)
                pthread_mutex_destroy(&table->philo[i]->time_lock);
            error_cleaning(table, 'x');
        }
    }
}

void    init_table(t_table *table)
{
    int i;

    table->philo = malloc(sizeof(t_philo *) * table->philo_nbrs);
    if (table->philo == NULL)
        error_cleaning(table, 'm');
    i = -1;
    while (++i < table->philo_nbrs)
    {
        table->philo[i] = malloc(sizeof(t_philo));
        if (table->philo == NULL)
            error_cleaning(table, 'm');
    }
    fill_philos(table);
    init_mutex_fork(table);
    init_mutex_check(table);
}

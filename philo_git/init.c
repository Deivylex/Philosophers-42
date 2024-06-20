/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:45:33 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/20 14:48:39 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int contador = 0;

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
            while (--i >= 0)
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
            while (--i >= 0)
                pthread_mutex_destroy(&table->philo[i]->meal_lock);
            error_cleaning(table, 'x');
        }
    }
    i = -1;
    while (++i < table->philo_nbrs)
    {
        if (pthread_mutex_init(&table->philo[i]->time_lock, NULL))
        {
            while (--i >= 0)
                pthread_mutex_destroy(&table->philo[i]->time_lock);
            error_cleaning(table, 'x');
        }
    }
}
void    eating_step(t_philo *philo)
{
    //conotinuar con la rutina
}

void    *philo_simulation(void *arg)
{
    t_philo *philo;

    philo = arg;


    pthread_mutex_lock(&philo->meal_lock);
    contador++;
    printf("%d\n", contador);
    pthread_mutex_unlock(&philo->meal_lock);
    return NULL;
}

void    create_threads(t_table *table)
{
    int i;

    table->start_time = 0;
    i = -1;
    while (++i < table->philo_nbrs)
    {
        pthread_create(&table->philo[i]->thread, NULL, &philo_simulation,
                    table->philo[i]);
    }
    i = -1;
    while (++i < table->philo_nbrs)
    {
        pthread_join(table->philo[i]->thread, NULL);
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
        if (table->philo[i] == NULL)
            error_cleaning(table, 'm');
    }
    fill_philos(table);
    init_mutex_fork(table);
    init_mutex_check(table);
    create_threads(table);
    printf("cont %d\n", contador);
}

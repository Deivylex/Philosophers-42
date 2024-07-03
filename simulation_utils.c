/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:23:33 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/03 15:07:20 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_dead(t_philo *philo)
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
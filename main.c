/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:45:07 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/25 16:04:58 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"
# include <stdio.h>

int main(int ac, char **av)
{
    t_table     table;
    t_philo     philo; 
    int result;
    int i; 
    
    if (ac < 5)
        philo_error("Missing arguments\n");
    if (ac > 6)
        philo_error("Too many arguments\n");
    make_arguments(av, &table);
    init_table(&table);
    join_thread(&table, table.philo_nbrs);
/*     i = 0;
    while (i < table.philo_nbrs)
    {
        printf ("philo{%d} id [%d] fork0 [%d] fork1 [%d] n_meals [%d]\n", i, table.philo[i]->id, table.philo[i]->forks[0], table.philo[i]->forks[1], table.philo[i]->n_meals);
        i++;
    } */
}
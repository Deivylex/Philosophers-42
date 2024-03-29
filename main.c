/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:18:04 by dzurita           #+#    #+#             */
/*   Updated: 2024/03/29 17:10:05 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void *mi_funcion(void *arg) 
{
    thread_args *args = (thread_args *)arg;
    printf("¡Hola desde el hilo %d!\n", args->index);
    return(0);
}

int main(int ac, char **av)
{
    t_data      content;
    pthread_t   hilo[5];
    thread_args *args;
    int result;
    int i;
    
    if (ac < 5)
        philo_error("Missing arguments\n");
    if (ac > 6)
        philo_error("Too many arguments\n");
    make_arguments(av, &content);
    i = 0;
    while (i < 5)
    {
        args = malloc(sizeof(thread_args));
        if (args == NULL) {
            return 1;
        }
        args->index = i;
        args->content = &content;    
        result = pthread_create(&hilo[i], NULL, mi_funcion, args);
        if(result)
            return(1);
        i++;
    }
    i = 0;
    while (i > 5)
    {
        pthread_join(hilo[i], NULL);
        i++;
    }
}
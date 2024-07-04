/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:17:28 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/03 16:29:08 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep_ms(long time, t_philo *philo)
{
	long	delay_ms;

	delay_ms = get_time() + time;
	while (get_time() < delay_ms)
	{
		if (philo_dead(philo) == 1)
			break ;
		usleep(500);
	}
}

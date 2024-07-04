/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:46:26 by dzurita           #+#    #+#             */
/*   Updated: 2024/07/03 19:52:51 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(t_table *table, const char *nptr)
{
	int		sign;
	long	num;

	while ((*nptr == ' ') || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	num *= sign;
	if (num <= 0 || num > 2147483647)
	{
		philo_error(table, "Invalid numbers\n");
		return (-1);
	}
	return (num);
}

int	ft_check_parameters(char *str)
{
	if (!(*str == '+' || *str == '-' || (*str >= '0' && *str <= '9')))
		return (1);
	if ((*str == '+' || *str == '-') && !(str[1] >= '0' && str[1] <= '9'))
		return (1);
	while (*++str)
		if (!(*str >= '0' && *str <= '9'))
			return (1);
	return (0);
}

void	make_arguments(char **av, t_table *content)
{
	int	i;

	if (content->exit_status)
		return ;
	i = 0;
	while (av[++i])
	{
		if (ft_check_parameters(av[i]))
			philo_error(content, "Syntax error\n");
	}
	content->philo_nbrs = ft_atol(content, av[1]);
	i = 2;
	while (i < 5)
	{
		if ((ft_atol(content, av[i]) * MS) < 60 * MS)
			philo_error(content, "Timestamps need to be mayor tham 60ms\n");
		i++;
	}
	content->time_die = ft_atol(content, av[2]);
	content->time_eat = ft_atol(content, av[3]);
	content->time_sleep = ft_atol(content, av[4]);
	if (av[5])
		content->max_meals = ft_atol(content, av[5]);
	else
		content->max_meals = -1;
}

void	error_cleaning(t_table *table, char type)
{
	int	i;

	if (table->exit_status)
		return ;
	if (type == 'm')
		ft_putstr_fd("fatal error malloc\n", 2);
	if (type == 'x')
		ft_putstr_fd("fatal error mutex\n", 2);
	if (type == 'j')
		ft_putstr_fd("fatal error pthread join\n", 2);
	if (type == 'p')
		ft_putstr_fd("fatal error creating theread\n", 2);
	if (table->forks_lock)
		free (table->forks_lock);
	if (table->philo[0])
	{
		i = -1;
		while (++i < table->philo_nbrs && table->philo[i])
			free(table->philo[i]);
		free(table->philo);
	}
	table->exit_status = 1;
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}

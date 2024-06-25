# include "philo.h"

void    philo_error(const char *str)
{
    printf("%s", str);
    exit(1);
}
size_t	ft_nbr_len(const	char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_atol(const char *nptr)
{
	int		sign;
	long	num;

	if (ft_nbr_len(nptr) > 10)
		philo_error("Number too big\n");
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
        philo_error("Invalid numbers\n");
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
void    make_arguments(char **av, t_table *content)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (ft_check_parameters(av[i]))
			philo_error("Syntax error\n");
		i++;
	}
    content->philo_nbrs = ft_atol(av[1]);
	i = 2;
	while (i < 5)
	{
		if ((ft_atol(av[i]) * ms) < 60 * ms)
			philo_error("Timestamps need to be mayor tham 60ms");
		i++;
	}
    content->time_die = ft_atol(av[2]) * ms;
    content->time_eat = ft_atol(av[3]) * ms;
    content->time_sleep = ft_atol(av[4]) * ms;
    if (av[5])
        content->max_meals = ft_atol(av[5]);
    else
        content->max_meals = -1;
}

void error_cleaning(t_table *table, char type)
{
	int i;

	if (type == 'm')
		printf("fatal error malloc\n");
	if (type == 'x')
		printf("fatal error mutex\n");
	if (table->forks_lock)
		free (table->forks_lock);
	i = 0;
	while (table->philo[i]) 
	{
		free (table->philo[i]);
		i++;
	}
	exit(1);
}
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

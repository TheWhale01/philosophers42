/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:24:19 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/22 14:10:56 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

int	check(int ac, char **av)
{
	int	i;
	int	nb;

	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	while (++i < ac)
	{
		nb = ft_atoll(av[i]);
		if (ft_strlen(av[i]) > 10)
			return (0);
		else if (nb < 0 || nb > INT_MAX)
			return (0);
	}
	return (1);
}

unsigned int	get_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->write);
	printf("%u %d ", get_ms() - philo->env->start_time, philo->id);
	if (philo->state == SLEEP)
		printf("is sleeping\n");
	else if (philo->state == THINK)
		printf("is thinking\n");
	else if (philo->state == EAT)
		printf("is eating\n");
	else if (philo->state == DEAD)
		printf("died\n");
	else if (philo->state == FORKS)
		printf("has taken a fork\n");
	pthread_mutex_unlock(&philo->env->write);
}

void	free_philo(t_philo *philos)
{
	(void)philos;
}

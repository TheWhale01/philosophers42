/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:24:19 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/04 09:24:26 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void	ft_sleep(unsigned int ms)
{
	int	start;

	start = get_ms();
	while ((get_ms() - start) < ms)
		usleep(ms / 10);
}

int	check(int ac, char **av)
{
	int	i;
	int	nb;

	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	if (!ft_atoll(av[1]))
		return (0);
	while (++i < ac)
	{
		nb = ft_atoll(av[i]);
		if (ft_strlen(av[i]) > 10 || !ft_is_number(av[i])
			|| (nb < 0 || nb > INT_MAX))
			return (0);
	}
	return (1);
}

void	free_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->env->nb_philos)
	{
		pthread_cancel(philos[i].thread);
		pthread_join(philos[i].thread, NULL);
	}
	free(philos->env->forks);
	free(philos->env);
	free(philos);
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
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->env->write);
		return ;
	}
	printf("%u %d ", get_ms() - philo->env->start_time, philo->id);
	if (philo->state == SLEEP)
		printf("is sleeping\n");
	else if (philo->state == THINK)
		printf("is thinking\n");
	else if (philo->state == EAT)
		printf("is eating\n");
	else if (philo->state == FORKS)
		printf("has taken a fork\n");
	pthread_mutex_unlock(&philo->env->write);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:51:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/06 15:01:47 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	check_eat(t_philo *philos)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philos->env->eat);
	if (philos->env->limit_eat == -1)
	{
		pthread_mutex_unlock(&philos->env->eat);
		return (0);
	}
	while (++i < philos->env->nb_philos)
	{
		if (philos[i].nb_eat < philos[i].env->limit_eat)
		{
			pthread_mutex_unlock(&philos->env->eat);
			return (0);
		}
	}
	pthread_mutex_unlock(&philos->env->eat);
	return (1);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->death);
	if (philo->env->died == 1)
	{
		pthread_mutex_unlock(&philo->env->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->death);
	return (0);
}

void	check_end(t_philo *philos)
{
	int	i;

	i = 0;
	while (1)
	{
		philo_death(&philos[i]);
		if (check_death(&philos[i]))
		{
			pthread_mutex_lock(&philos->env->write);
			printf("%d %d died\n", get_ms() - philos->env->start_time,
				philos[i].id);
			pthread_mutex_unlock(&philos->env->write);
			break ;
		}
		if (check_eat(philos))
			break ;
		i++;
		if (i == philos->env->nb_philos)
			i = 0;
	}
}

void	*live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!check_death(philo)
		&& (philo->nb_eat < philo->env->limit_eat
			|| philo->env->limit_eat == -1))
	{
		philo_eat(philo);
		philo_sleep_think(philo, SLEEP);
		philo_sleep_think(philo, THINK);
	}
	return (NULL);
}

void	launch(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->env->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, live, &philos[i]))
		{
			printf("Could not create all threads.\n");
			philos->env->nb_philos = i;
			philos->env->died = 1;
		}
	}
	check_end(philos);
	free_philos(philos);
}

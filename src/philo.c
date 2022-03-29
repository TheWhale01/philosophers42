/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:51:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/29 14:56:33 by hubretec         ###   ########.fr       */
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
	pthread_mutex_lock(&philos->env->actions);
	if (philos->env->limit_eat == -1)
	{
		pthread_mutex_unlock(&philos->env->actions);
		return (0);
	}
	while (++i < philos->env->nb_philos)
	{
		if (philos[i].nb_eat < philos[i].env->limit_eat)
		{
			pthread_mutex_unlock(&philos->env->actions);
			return (0);
		}
	}
	pthread_mutex_unlock(&philos->env->actions);
	return (1);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->death);
	if (philo->env->died)
	{
		pthread_mutex_unlock(&philo->env->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->death);
	return (0);
}

void	*live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!check_death(philo))
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
		pthread_create(&philos[i].thread, NULL, live, &philos[i]);
}

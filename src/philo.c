/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:51:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/04 09:15:52 by hubretec         ###   ########.fr       */
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
	else if (philo->env->died > 1)
	{
		pthread_mutex_unlock(&philo->env->death);
		return (2);
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
	i = 0;
	while (1)
	{
		if (check_death(&philos[i]) == 1)
		{
			pthread_mutex_lock(&philos->env->write);
			pthread_mutex_lock(&philos->env->death);
			philos->env->died++;
			pthread_mutex_unlock(&philos->env->death);
			printf("%d %d died\n", get_ms() - philos->env->start_time,
				philos[i].id);
			pthread_mutex_unlock(&philos->env->write);
			break ;
		}
		philo_death(&philos[i]);
		i++;
		if (i == philos->env->nb_philos)
			i = 0;
	}
	free_philos(philos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:51:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/22 15:22:04 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!philo->env->died)
	{
		philo_eat(philo);
		philo_sleep_think(philo, SLEEP);
		philo_sleep_think(philo, THINK);
	}
	return (NULL);
}

int	check_eat(t_philo *philos)
{
	int	i;

	i = -1;
	if (philos->env->limit_eat == -1)
		return (0);
	while (++i < philos->env->nb_philos)
		if (philos[i].nb_eat < philos[i].env->limit_eat)
			return (0);
	return (1);
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
		if (philos[i].env->died || check_eat(philos))
		{
			free_philo(philos);
			break ;
		}
		if (i == philos->env->nb_philos - 1)
			i = 0;
		i++;
	}
}

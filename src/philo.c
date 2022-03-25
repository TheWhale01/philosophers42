/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:51:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/25 10:28:36 by hubretec         ###   ########.fr       */
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
	if (philos->env->limit_eat == -1)
		return (0);
	while (++i < philos->env->nb_philos)
		if (philos[i].nb_eat < philos[i].env->limit_eat)
			return (0);
	return (1);
}

void	*live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!philo->env->died)
	{
		philo_eat(philo);
		philo_sleep_think(philo, SLEEP);
		philo_sleep_think(philo, THINK);
		philo_death(philo);
	}
	return (NULL);
}

void	launch(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->env->nb_philos)
		pthread_create(&philos[i].thread, NULL, live, &philos[i]);
	while (1)
	{
		if (check_eat(philos) || philos->env->died)
		{
			printf("%u %d died\n", (get_ms() - philos->env->start_time),
				philos->env->died);
			free_philo(philos);
			exit(EXIT_SUCCESS);
		}
	}
}

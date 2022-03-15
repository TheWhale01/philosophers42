/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:26:35 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/15 14:07:35 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	philo->fork_r = (&philo->fork_l) + 1;
	*((&philo->fork_l) + 1) = 0;
	printf("philo %d has taken a fork\nphilo %d is eating\n",
		philo->id, philo->id);
	usleep(philo->env->time_to_eat);
	*((&philo->fork_l) + 1) = 1;
	philo->fork_r = NULL;
	pthread_mutex_unlock(&philo->mutex_fork);
}

void	philo_sleep(t_philo *philo)
{
	printf("philo %d is sleeping\n", philo->id);
	usleep(philo->env->time_to_sleep);
}

void	*live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		philo_eat(philo);
	else
		philo_sleep(philo);
	return (NULL);
}

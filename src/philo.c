/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:26:35 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/15 17:35:01 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_philo	*next_philo;

	next_philo = philo + 1;
	if (philo->id == philo->env->nb_philos)
		next_philo = philo - philo->id;
	pthread_mutex_lock(&philo->mutex_fork);
	philo->fork_l = 1;
	philo->fork_r = &(next_philo->fork_l);
	philo->state = EAT;
	printf("philo %d has taken a fork\nphilo %d has taken a fork\n",
		philo->id, philo->id);
	print_state(philo);
	usleep(philo->env->time_to_eat);
	philo->fork_l = 0;
	philo->fork_r = NULL;
	pthread_mutex_unlock(&philo->mutex_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->mutex_sleep);
	philo->state = SLEEP;
	print_state(philo);
	usleep(philo->env->time_to_sleep);
	pthread_mutex_unlock(&philo->env->mutex_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->mutex_think);
	philo->state = THINK;
	print_state(philo);
	pthread_mutex_unlock(&philo->env->mutex_think);
}

void	check_death(t_philo *philo)
{
	philo->state = DEAD;
}

void	*live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		philo_eat(philo);
	while (philo->state != DEAD)
	{
		philo_sleep(philo);
		philo_think(philo);
		philo_eat(philo);
		// check_death(philo);
	}
	return (NULL);
}

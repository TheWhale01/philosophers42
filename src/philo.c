/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:26:35 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/17 14:54:29 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	philo->state = FORKS;
	print_state(philo);
	pthread_mutex_lock(philo->mutex_next_fork);
	print_state(philo);
	philo->last_meal = get_ms() - philo->last_meal;
	usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(philo->mutex_next_fork);
	pthread_mutex_unlock(&philo->mutex_fork);
	if (philo->env->nb_eat != -1)
		philo->env->nb_eat--;
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
	if (philo->last_meal > philo->env->time_to_die)
	{
		print_state(philo);
		philo->state = DEAD;
	}
}

void	*live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		philo_eat(philo);
	while (philo->state != FINISHED && philo->state != DEAD)
	{
		philo_sleep(philo);
		philo_think(philo);
		philo_eat(philo);
		check_death(philo);
		philo->env->start_time += get_ms();
		if (!philo->env->nb_eat)
			philo->state = FINISHED;
	}
	return (NULL);
}

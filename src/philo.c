/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:26:35 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/18 16:02:03 by hubretec         ###   ########.fr       */
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
	if (philo->env->nb_philos == 1)
	{
		philo->state = DEAD;
		return ;
	}
	pthread_mutex_lock(philo->mutex_next_fork);
	print_state(philo);
	philo->last_meal = 0;
	philo->state = EAT;
	print_state(philo);
	usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(philo->mutex_next_fork);
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
	pthread_mutex_lock(&philo->env->mutex_death);
	philo->last_meal = philo->env->start_time - philo->last_meal;
	if (philo->last_meal > philo->env->time_to_die)
	{
		philo->state = DEAD;
		print_state(philo);
	}
	pthread_mutex_unlock(&philo->env->mutex_death);
}

void	*live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->state != FINISHED && philo->state != DEAD)
	{
		pthread_mutex_lock(&philo->env->mutex_write);
		philo->env->start_time = get_ms() - philo->env->start_time;
		pthread_mutex_unlock(&philo->env->mutex_write);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		check_death(philo);
		if (philo->env->nb_eat > 0)
			philo->env->nb_eat--;
		else if (!philo->env->nb_eat)
			philo->state = FINISHED;
	}
	return (NULL);
}

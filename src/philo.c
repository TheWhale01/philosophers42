/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:26:35 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/18 16:08:45 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	print_state(philo);
	pthread_mutex_lock(philo->mutex_next_fork);
	print_state(philo);
	philo->last_meal = 0;
	print_state(philo);
	usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(philo->mutex_next_fork);
	pthread_mutex_unlock(&philo->mutex_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->mutex_sleep);
	print_state(philo);
	usleep(philo->env->time_to_sleep);
	pthread_mutex_unlock(&philo->env->mutex_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->mutex_think);
	print_state(philo);
	pthread_mutex_unlock(&philo->env->mutex_think);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->mutex_death);
	philo->last_meal = philo->env->start_time - philo->last_meal;
	if (philo->last_meal > philo->env->time_to_die)
		print_state(philo);
	pthread_mutex_unlock(&philo->env->mutex_death);
}

void	*live(void *ptr)
{
	t_main	*main_thread;

	main_thread = (t_main *)ptr;
	while (main_thread->died && main_thread->all_eaten)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		check_death(philo);
	}
	return (NULL);
}

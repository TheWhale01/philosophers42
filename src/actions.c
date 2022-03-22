/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:06:34 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/22 14:21:18 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	take_forks(t_philo *philo)
{
	if (philo->id == philo->env->nb_philos)
	{
		pthread_mutex_lock(&philo->env->forks[0]);
		philo->state = FORKS;
		print_state(philo);
		pthread_mutex_lock(&philo->env->forks[philo->id - 1]);
		print_state(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->env->forks[philo->id - 1]);
		philo->state = FORKS;
		print_state(philo);
		pthread_mutex_lock(&philo->env->forks[philo->id]);
		print_state(philo);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id == philo->env->nb_philos)
	{
		pthread_mutex_unlock(&philo->env->forks[0]);
		pthread_mutex_unlock(&philo->env->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->env->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->env->forks[philo->id]);
	}
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	philo->nb_eat++;
	philo->state = EAT;
	print_state(philo);
	usleep(philo->env->time_to_eat);
	drop_forks(philo);
}

void	philo_sleep_think(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->env->actions);
	philo->state = state;
	print_state(philo);
	if (state == SLEEP)
		usleep(philo->env->time_to_sleep);
	pthread_mutex_unlock(&philo->env->actions);
}

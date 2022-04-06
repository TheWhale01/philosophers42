/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:06:34 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/06 14:58:00 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	take_forks(t_philo *philo)
{
	if (philo->id == philo->env->nb_philos)
	{
		pthread_mutex_lock(&philo->env->forks[0]);
		philo->state = FORKS;
		print_state(philo);
		if (philo->env->nb_philos == 1)
		{
			pthread_mutex_unlock(&philo->env->forks[0]);
			ft_sleep(philo->env->time_to_eat);
			pthread_mutex_lock(&philo->env->death);
			philo->env->died = 1;
			pthread_mutex_unlock(&philo->env->death);
			return ;
		}
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
	if (philo->env->nb_philos == 1)
		return ;
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

void	philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->death);
	if ((get_ms() - philo->env->start_time) - philo->last_meal
		> (unsigned int)philo->env->time_to_die)
		philo->env->died = 1;
	pthread_mutex_unlock(&philo->env->death);
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	philo->nb_eat++;
	philo->state = EAT;
	pthread_mutex_lock(&philo->env->death);
	philo->last_meal = get_ms() - philo->env->start_time;
	pthread_mutex_unlock(&philo->env->death);
	print_state(philo);
	drop_forks(philo);
	ft_sleep(philo->env->time_to_eat);
}

void	philo_sleep_think(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->env->actions);
	philo->state = state;
	print_state(philo);
	pthread_mutex_unlock(&philo->env->actions);
	if (state == SLEEP)
		ft_sleep(philo->env->time_to_sleep);
}

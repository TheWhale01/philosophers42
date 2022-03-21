/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:55:19 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/21 14:32:16 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	take_forks(t_main *main_thread, int id)
{
	main_thread->philos[id - 1]->state = FORKS;
	if (id == main_thread->nb_philo)
	{
		pthread_mutex_lock(&main_thread->forks[0]);
		print_state(main_thread->philos[id - 1], &main_thread->write);
		pthread_mutex_lock(&main_thread->forks[id - 1]);
		print_state(main_thread->philos[id - 1], &main_thread->write);
	}
	else
	{
		pthread_mutex_lock(&main_thread->forks[id - 1]);
		print_state(main_thread->philos[id - 1], &main_thread->write);
		pthread_mutex_lock(&main_thread->forks[id]);
		print_state(main_thread->philos[id - 1], &main_thread->write);
	}
}

void	drop_forks(t_main *main_thread, int id)
{
	if (id == main_thread->nb_philo)
	{
		pthread_mutex_unlock(&main_thread->forks[0]);
		print_state(main_thread->philos[id - 1], &main_thread->write);
		pthread_mutex_unlock(&main_thread->forks[id - 1]);
		print_state(main_thread->philos[id - 1], &main_thread->write);
	}
	else
	{
		pthread_mutex_unlock(&main_thread->forks[id - 1]);
		print_state(main_thread->philos[id - 1], &main_thread->write);
		pthread_mutex_unlock(&main_thread->forks[id]);
		print_state(main_thread->philos[id - 1], &main_thread->write);
	}
}

void	philo_eat(t_main *main_thread, int id)
{
	take_forks(main_thread, id);
	check_eat(main_thread);
	main_thread->philos[id - 1]->nb_eat++;
	main_thread->philos[id - 1]->state = EAT;
	print_state(main_thread->philos[id - 1], &main_thread->write);
	usleep(main_thread->time_to_eat);
	drop_forks(main_thread, id);
}

void	philo_sleep_think(t_main *main_thread, int id, int state)
{
	pthread_mutex_lock(&main_thread->actions);
	main_thread->philos[id - 1]->state = state;
	print_state(main_thread->philos[id - 1], &main_thread->write);
	pthread_mutex_unlock(&main_thread->actions);
}

void	*live(void *ptr)
{
	int		i;
	t_main	*main_thread;

	main_thread = (t_main *)ptr;
	while (!main_thread->died)
	{
		i = -1;
		while (++i < main_thread->nb_philo)
		{
			philo_eat(main_thread, i + 1);
			philo_sleep_think(main_thread, i + 1, SLEEP);
			philo_sleep_think(main_thread, i + 1, THINK);
		}
	}
	return (NULL);
}

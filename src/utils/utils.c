/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:24:10 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/18 16:25:07 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "philo.h"

void	*free_philo(t_main *main_thread, int len)
{
	int	i;

	i = 0;
	while (main_thread->philo_tab && main_thread->philo_tab[i] && i < len)
	{
		pthread_mutex_destroy(&main_thread->philo_tab[i]->mutex_fork);
		pthread_mutex_destroy(main_thread->philo_tab[i]->mutex_next_fork);
		pthread_mutex_destroy(&main_thread->philo_tab[i]->env->mutex_death);
		pthread_mutex_destroy(&main_thread->philo_tab[i]->env->mutex_sleep);
		pthread_mutex_destroy(&main_thread->philo_tab[i]->env->mutex_write);
		pthread_mutex_destroy(&main_thread->philo_tab[i]->env->mutex_think);
		pthread_join(main_thread->philo_tab[i++], NULL);
		free(main_thread->philo_tab[i]);
	}
	free(main_thread->philo_tab);
	free(main_thread);
	return (NULL);
}

void	exit_msg(int exit_code, char *str, t_main *main_thread)
{
	if (str)
		printf("%s\n", str);
	if (main_thread)
		free_philo(main_thread, main_thread->nb_philos);
	exit(exit_code);
}

unsigned int	get_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:24:10 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/17 14:50:38 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "philo.h"

void	print_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->mutex_write);
	printf("%u %d ", philo->env->start_time, philo->id);
	if (philo->state == EAT)
		printf("is eating\n");
	else if (philo->state == SLEEP)
		printf("is sleeping\n");
	else if (philo->state == THINK)
		printf("is thinking\n");
	else if (philo->state == DEAD)
		printf("died\n");
	else if (philo->state == FORKS)
		printf("has taken a fork\n");
	pthread_mutex_unlock(&philo->env->mutex_write);
}

void	*free_philo(t_philo **tab, int len)
{
	int	i;

	i = 0;
	while (tab && tab[i] && i < len)
	{
		pthread_join(tab[i]->thread, NULL);
		free(tab[i++]);
	}
	free(tab);
	return (NULL);
}

void	exit_msg(int exit_code, char *str)
{
	if (str)
		printf("%s\n", str);
	exit(exit_code);
}

unsigned int	get_ms(void)
{
	unsigned int	ms;

	ms = 0;
	return (ms);
}

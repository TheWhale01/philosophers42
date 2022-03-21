/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:07:15 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/21 14:45:32 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	exit_msg(int exit_code, char *str)
{
	if (str)
		printf("%s\n", str);
	exit(exit_code);
}

void	free_main_thread(t_main *main_thread)
{
	int	i;

	i = -1;
	while (main_thread->philos[++i])
	{
		pthread_join(main_thread->philos[i]->thread, NULL);
		free(main_thread->philos[i]);
	}
	free(main_thread->philos);
	free(main_thread);
}

void	print_state(t_philo *philo, pthread_mutex_t *write)
{
	pthread_mutex_lock(write);
	printf("%d ", philo->id);
	if (philo->state == EAT)
		printf("is eating\n");
	else if (philo->state == SLEEP)
		printf("is sleeping\n");
	else if (philo->state == DEAD)
		printf("is dead\n");
	else if (philo->state == THINK)
		printf("is thinking\n");
	else if (philo->state == FORKS)
		printf("has taken a fork\n");
	pthread_mutex_unlock(write);
}

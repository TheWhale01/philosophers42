/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:26:35 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/14 16:29:42 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "philo.h"

void	check_death(t_philo **philo_tab)
{
	int	i;

	i = -1;
	while (++i < philo_tab[i]->env->nb_philos)
		if (philo_tab[i]->last_meal > philo_tab[i]->env->time_to_die)
			printf("Philo %d died\n", philo_tab[i]->id);
}
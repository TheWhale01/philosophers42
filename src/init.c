/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:17:15 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/14 11:24:55 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	*tell(void *ptr)
{
	(void)ptr;
	printf("New thread created\n");
	return (NULL);
}

t_philo	*create_philo(void)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * 1);
	if (!philo)
		return (NULL);
	philo->fork_l = 1;
	philo->fork_r = NULL;
	philo->state = EAT;
	pthread_create(&(philo->thread), NULL, &tell, NULL);
	return (philo);
}

t_philo	**create_philos(int nb_philo)
{
	int		i;
	t_philo	**philo_tab;

	philo_tab = malloc(sizeof(t_philo *) * (nb_philo + 1));
	if (!philo_tab)
		return (0);
	i = -1;
	while (++i < nb_philo)
		philo_tab[i] = create_philo();
	philo_tab[i] = NULL;
	return (philo_tab);
}

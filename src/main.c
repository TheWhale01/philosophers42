/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:58:08 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/09 12:16:42 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	free_philo(t_philo **philo_tab)
{
	int	i;

	i = -1;
	while (philo_tab[++i])
		free(philo_tab[i]);
	free(philo_tab);
}

void	*tell()
{
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

int	main(int ac, char **av)
{
	int		i;
	int		nb_philo;
	t_philo	**philo_tab;

	if (ac != 2)
		return (0);
	nb_philo = ft_atoi(av[1]);
	philo_tab = malloc(sizeof(t_philo *) * (nb_philo + 1));
	if (!philo_tab)
		return (0);
	i = -1;
	while (++i < nb_philo)
		philo_tab[i] = create_philo();
	philo_tab[i] = NULL;
	i = -1;
	while (philo_tab[++i])
		pthread_join(philo_tab[i]->thread, NULL);
	free_philo(philo_tab);
	return (0);
}

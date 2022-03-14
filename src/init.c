/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:17:15 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/14 16:27:31 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	*tell(void *ptr)
{
	(void)ptr;
	printf("New philo created\n");
	return (NULL);
}

t_env	*create_env(int ac, char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env) * 1);
	if (!env)
		return (NULL);
	env->nb_eat = -1;
	if (ac == 6)
		env->nb_eat = ft_atoi(av[5]);
	env->nb_philos = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	return (env);
}

t_philo	*create_philo(int ac, char **av, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * 1);
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->fork_l = 1;
	philo->fork_r = NULL;
	philo->state = EAT;
	philo->last_meal = 0;
	philo->env = create_env(ac, av);
	if (!philo->env)
	{
		free(philo);
		return (NULL);
	}
	pthread_create(&(philo->thread), NULL, &tell, NULL);
	return (philo);
}

t_philo	**create_philos(int ac, char **av)
{
	int		i;
	int		nb_philo;
	t_philo	**philo_tab;

	nb_philo = ft_atoi(av[1]);
	philo_tab = malloc(sizeof(t_philo *) * (nb_philo + 1));
	if (!philo_tab)
		return (0);
	i = -1;
	while (++i < nb_philo)
	{
		philo_tab[i] = create_philo(ac, av, i + 1);
		if (!philo_tab[i] || !philo_tab[i]->env)
			return (free_philo(philo_tab, i + 1));
	}
	philo_tab[i] = NULL;
	return (philo_tab);
}

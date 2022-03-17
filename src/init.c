/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:17:15 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/17 14:31:58 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	init_threads(t_philo **philo_tab)
{
	int	i;

	i = -1;
	while (philo_tab[++i])
		pthread_create(&philo_tab[i]->thread, NULL, &live, philo_tab[i]);
}

void	init_forks(t_philo **philo_tab)
{
	int	i;

	i = -1;
	while (philo_tab[++i])
	{
		pthread_mutex_init(&philo_tab[i]->mutex_fork, NULL);
		pthread_mutex_init(philo_tab[i]->mutex_next_fork, NULL);
		if (i + 1 != (*philo_tab)->env->nb_philos)
			philo_tab[i]->mutex_next_fork = &philo_tab[i + 1]->mutex_fork;
		else
			philo_tab[i]->mutex_next_fork = &philo_tab[0]->mutex_fork;
	}
}

t_env	*create_env(int ac, char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env) * 1);
	if (!env)
		exit_msg(EXIT_FAILURE, "Memory error");
	env->nb_eat = -1;
	if (ac == 6)
		env->nb_eat = ft_atoi(av[5]);
	env->nb_philos = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&env->mutex_sleep, NULL);
	pthread_mutex_init(&env->mutex_think, NULL);
	pthread_mutex_init(&env->mutex_write, NULL);
	return (env);
}

t_philo	*create_philo(int id, t_env *env)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * 1);
	if (!philo)
		return (NULL);
	philo->mutex_next_fork = malloc(sizeof(pthread_mutex_t) * 1);
	if (!philo->mutex_next_fork)
	{
		free(philo);
		return (NULL);
	}
	philo->id = id;
	philo->env = env;
	philo->state = SLEEP;
	philo->last_meal = 0;
	return (philo);
}

t_philo	**create_philos(int nb_philo, t_env *env)
{
	int		i;
	t_philo	**philo_tab;

	philo_tab = malloc(sizeof(t_philo *) * (nb_philo + 1));
	if (!philo_tab)
		return (0);
	i = -1;
	while (++i < nb_philo)
	{
		philo_tab[i] = create_philo(i + 1, env);
		if (!philo_tab[i] || !philo_tab[i]->env)
			return (free_philo(philo_tab, i + 1));
	}
	env->start_time = get_ms();
	philo_tab[i] = NULL;
	init_forks(philo_tab);
	init_threads(philo_tab);
	return (philo_tab);
}

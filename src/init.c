/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:17:15 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/18 16:44:31 by hubretec         ###   ########.fr       */
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

void	init_forks(t_main *main_thread)
{
	int	i;

	i = -1;
	while (main_thread->philo_tab[++i])
	{
		pthread_mutex_init(&main_thread->philo_tab[i]->mutex_fork, NULL);
		pthread_mutex_init(main_thread->philo_tab[i]->mutex_next_fork, NULL);
		if (i + 1 != main_thread->nb_philos)
			main_thread->philo_tab[i]->mutex_next_fork
				= &main_thread->philo_tab[i + 1]->mutex_fork;
		else
			main_thread->philo_tab[i]->mutex_next_fork
				= &main_thread->philo_tab[0]->mutex_fork;
	}
}

t_env	*create_env(int ac, char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env) * 1);
	if (!env)
		exit_msg(EXIT_FAILURE, "Memory error", NULL);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	if (env->time_to_die <= 0 || env->time_to_eat <= 0
		|| env->time_to_sleep <= 0)
		exit_msg(EXIT_FAILURE, "Args must be greater than zero.", NULL);
	pthread_mutex_init(&env->mutex_sleep, NULL);
	pthread_mutex_init(&env->mutex_think, NULL);
	pthread_mutex_init(&env->mutex_write, NULL);
	pthread_mutex_init(&env->mutex_death, NULL);
	return (env);
}

void	create_philo(t_main *main_thread, t_env *env)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < main_thread->nb_philos)
	{
		main_thread->philo_tab[i] = malloc(sizeof(t_philo) * 1);
		if (!philo)
			exit_msg(EXIT_FAILURE, "Memory error.", main_thread);
		philo->mutex_next_fork = malloc(sizeof(pthread_mutex_t) * 1);
		if (!philo->mutex_next_fork)
			exit_msg(EXIT_FAILURE, "Memory error.", main_thread);
		philo->id = i + 1;
		philo->env = env;
		philo->last_meal = 0;
	}
}

t_main	*create_philos(int ac, char **av, t_env *env)
{
	int		i;
	t_main	*main_thread;

	main_thread = malloc(sizeof(t_main) * 1);
	if (!main_thread)
		exit_msg(EXIT_FAILURE, "Memory error.", NULL);
	main_thread->died = 0;
	main_thread->nb_eat = -1;
	if (ac == 6)
		main_thread->nb_eat = ft_atoi(av[5]);
	main_thread->nb_philos = ft_atoi(av[1]);
	if (main_thread->nb_philos <= 0)
		exit_msg(EXIT_FAILURE, "Args must be greater than zero.", main_thread);
	main_thread->philo_tab = malloc(sizeof(t_philo *)
			* (main_thread->nb_philos + 1));
	if (!main_thread->philo_tab)
		exit_msg(EXIT_FAILURE, "Memory error.", NULL);
	create_philo(main_thread, env);
	init_forks(main_thread->philo_tab);
	init_threads(main_thread->philo_tab);
	return (main_thread);
}

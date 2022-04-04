/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:23:27 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/03 14:36:50 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

t_philo	*init_philo(t_env *env)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * env->nb_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < env->nb_philos)
	{
		philos[i].nb_eat = 0;
		philos[i].id = i + 1;
		philos[i].env = env;
		philos[i].last_meal = 0;
	}
	return (philos);
}

void	init_env(t_env *env)
{
	int	i;

	i = -1;
	env->died = 0;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->nb_philos);
	if (!env->forks)
		return ;
	while (++i < env->nb_philos)
		pthread_mutex_init(&env->forks[i], NULL);
	pthread_mutex_init(&env->eat, NULL);
	pthread_mutex_init(&env->write, NULL);
	pthread_mutex_init(&env->actions, NULL);
	pthread_mutex_init(&env->death, NULL);
}

t_philo	*init(int ac, char **av)
{
	t_env	*env;
	t_philo	*philos;

	env = malloc(sizeof(t_env) * 1);
	if (!env)
		return (NULL);
	env->limit_eat = -1;
	if (ac == 6)
		env->limit_eat = ft_atoll(av[5]);
	env->start_time = get_ms();
	env->nb_philos = ft_atoll(av[1]);
	env->time_to_die = ft_atoll(av[2]);
	env->time_to_eat = ft_atoll(av[3]);
	env->time_to_sleep = ft_atoll(av[4]);
	init_env(env);
	philos = init_philo(env);
	return (philos);
}

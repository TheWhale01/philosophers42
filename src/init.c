/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:13:53 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/21 14:43:51 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	init_thread(t_main *main_thread)
{
	int	i;

	i = -1;
	while (++i < main_thread->nb_philo)
		pthread_create(&main_thread->philos[i]->thread,
			NULL, &live, main_thread);
}

void	init_forks(t_main *main_thread)
{
	int	i;

	main_thread->forks = malloc(sizeof(pthread_mutex_t)
			* main_thread->nb_philo);
	if (!main_thread->forks)
		exit_msg(EXIT_FAILURE, "Memory failure.");
	i = -1;
	while (++i < main_thread->nb_philo)
		pthread_mutex_init(&main_thread->forks[i], NULL);
}

void	init_philos(t_main *main_thread)
{
	int	i;

	i = -1;
	main_thread->philos = malloc(sizeof(t_philo *)
			* (main_thread->nb_philo + 1));
	if (!main_thread->philos)
		exit_msg(EXIT_FAILURE, "Memory failure.");
	while (++i < main_thread->nb_philo)
	{
		main_thread->philos[i] = malloc(sizeof(t_philo) * 1);
		if (!main_thread->philos[i])
			exit_msg(EXIT_FAILURE, "Memory failure.");
		main_thread->philos[i]->id = i + 1;
		main_thread->philos[i]->nb_eat = 0;
		pthread_mutex_init(&main_thread->write, NULL);
		pthread_mutex_init(&main_thread->actions, NULL);
	}
	main_thread->nb_eat = 0;
	main_thread->philos[i] = NULL;
	init_forks(main_thread);
	init_thread(main_thread);
}

t_main	*init_main_thread(int ac, char **av)
{
	t_main	*main_thread;

	check_args(ac, av);
	main_thread = malloc(sizeof(t_main) * 1);
	if (!main_thread)
		exit_msg(EXIT_FAILURE, "Memory failure.");
	main_thread->nb_eat = -1;
	if (ac == 6)
		main_thread->nb_eat = ft_atoi(av[5]);
	main_thread->died = 0;
	main_thread->nb_philo = ft_atoi(av[1]);
	main_thread->time_to_eat = ft_atoi(av[2]);
	main_thread->time_to_sleep = ft_atoi(av[3]);
	main_thread->time_to_die = ft_atoi(av[4]);
	init_philos(main_thread);
	return (main_thread);
}

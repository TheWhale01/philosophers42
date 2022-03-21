/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:06:34 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/21 14:39:07 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	check_args(int ac, char **av)
{
	int		i;
	int		nb;

	i = 0;
	if (ac < 5 || ac > 6)
		exit_msg(EXIT_FAILURE, "Wrong number of args.");
	nb = ft_atoi(av[1]);
	if (nb > 200)
		exit_msg(EXIT_FAILURE, "Too much philos.");
	while (++i < ac)
	{
		nb = ft_atoi(av[i]);
		if (nb < 0)
			exit_msg(EXIT_FAILURE, "Args must be positive.");
		else if (nb > INT_MAX)
			exit_msg(EXIT_FAILURE, "Too high values.");
	}
}

void	check_eat(t_main *main_thread)
{
	int	i;

	i = -1;
	while (++i < main_thread->nb_philo)
		if (main_thread->philos[i]->nb_eat > main_thread->nb_eat)
			exit_msg(EXIT_SUCCESS, NULL);
}

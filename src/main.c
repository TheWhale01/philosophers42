/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:58:08 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/15 13:19:00 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	main(int ac, char **av)
{
	int		nb_philo;
	t_env	*env;
	t_philo	**philo_tab;

	if (!(ac == 5 || ac == 6))
		return (0);
	nb_philo = ft_atoi(av[1]);
	if (nb_philo <= 0)
		return (0);
	env = create_env(ac, av);
	philo_tab = create_philos(nb_philo, env);
	free_philo(philo_tab, nb_philo);
	free(env);
	return (0);
}

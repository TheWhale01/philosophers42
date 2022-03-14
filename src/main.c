/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:58:08 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/14 14:25:43 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	main(int ac, char **av)
{
	int		nb_philo;
	t_philo	**philo_tab;

	if (!(ac == 5 || ac == 6))
		return (0);
	nb_philo = ft_atoi(av[1]);
	philo_tab = create_philos(ac, av);
	free_philo(philo_tab, nb_philo);
	return (0);
}

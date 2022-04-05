/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:15:40 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/05 14:35:43 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (!check(ac, av))
	{
		printf("Error\n");
		return (1);
	}
	philos = init(ac, av);
	launch(philos);
	return (0);
}

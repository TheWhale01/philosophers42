/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:17:15 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/09 12:28:26 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

t_philo	*create_philo(void)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * 1);
	if (!philo)
	return (philo);
}

t_philo	**create_philos(int nb_philo)
{
	int		i;
	t_philo	**tab;

	tab = malloc(sizeof(t_philo *) * (nb_philo + 1));
	if (!tab)
		exit_msg(EXIT_FAILURE, "Memory error.\n");
	i = -1;
	while (++i < nb_philo)
		tab[i] = create_philo();
	tab[i] = NULL;
	return (tab);
}

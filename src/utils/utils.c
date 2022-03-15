/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:24:10 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/15 17:48:31 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	print_state(t_philo *philo)
{
	ft_putstr("Philo ");
	ft_putnbr(philo->id);
	if (philo->state == EAT)
		ft_putstr(" is eating\n");
	else if (philo->state == SLEEP)
		ft_putstr(" is sleeping\n");
	else if (philo->state == THINK)
		ft_putstr(" is thinking\n");
}

void	*free_philo(t_philo **tab, int len)
{
	int	i;

	i = 0;
	while (tab && tab[i] && i < len)
	{
		pthread_join(tab[i]->thread, NULL);
		free(tab[i++]);
	}
	free(tab);
	return (NULL);
}

void	exit_msg(int exit_code, char *str)
{
	if (str)
		printf("%s\n", str);
	exit(exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:24:10 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/14 11:46:33 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	*free_philo(t_philo **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		pthread_join(tab[i]->thread, NULL);
		free(tab[i]);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:24:10 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/09 12:31:03 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	free_philo(t_philo **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(tab[i]);
	free(tab);
}

void	exit_msg(int exit_code, char *str)
{
	if (str)
		printf(str);
	exit(exit_code);
}

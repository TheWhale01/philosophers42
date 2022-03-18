/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:58:08 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/18 16:46:00 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	main(int ac, char **av)
{
	int		nb_philo;
	t_env	*env;
	t_main	*main_thread;

	if (!(ac == 5 || ac == 6))
		return (0);
	env = create_env(ac, av);
	main_thread = create_philos(av, av, env);
	free_philo(main_thread, main_thread->nb_philos);
	free(env);
	return (0);
}

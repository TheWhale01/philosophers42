/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:04:21 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/14 11:24:29 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define EAT 0
# define THINK 1
# define SLEEP 2

typedef struct s_philo
{
	int			*fork_r;
	int			fork_l;
	int			state;
	pthread_t	thread;
}	t_philo;

int		ft_atoi(const char *nptr);

void	exit_msg(int exit_code, char *str);

void	*free_philo(t_philo **tab, int len);

t_philo	**create_philos(int nb_philo);

#endif
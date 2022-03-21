/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:04:21 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/21 14:38:23 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define EAT 0
# define DEAD 1
# define SLEEP 2
# define THINK 3
# define FORKS 4

# define INT_MAX 2147483647

typedef struct s_philo
{
	int				id;
	int				state;
	int				nb_eat;
	pthread_t		thread;
}	t_philo;

typedef struct s_main
{
	int				died;
	int				nb_eat;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			**philos;
	pthread_mutex_t	write;
	pthread_mutex_t	actions;
	pthread_mutex_t	*forks;
}	t_main;

int		ft_atoi(const char *nptr);

void	check_args(int ac, char **av);
void	check_eat(t_main *main_thread);
void	exit_msg(int exit_code, char *str);
void	free_main_thread(t_main *main_thread);
void	print_state(t_philo *philo, pthread_mutex_t *write);

void	*live(void *ptr);

t_main	*init_main_thread(int ac, char **av);

#endif

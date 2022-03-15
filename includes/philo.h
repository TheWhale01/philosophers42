/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:04:21 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/15 17:45:02 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define EAT 0
# define DEAD 1
# define THINK 2
# define SLEEP 3

typedef struct s_env
{
	int				nb_eat;
	int				nb_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	pthread_mutex_t	mutex_sleep;
	pthread_mutex_t	mutex_think;
}	t_env;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				*fork_r;
	int				fork_l;
	int				state;
	t_env			*env;
	pthread_mutex_t	mutex_fork;
	pthread_t		thread;
}	t_philo;

int		ft_putstr(char *str);
int		ft_atoi(const char *nptr);

void	ft_putnbr(int nb);
void	print_state(t_philo *philo);
void	exit_msg(int exit_code, char *str);

void	*live(void *ptr);
void	*free_philo(t_philo **tab, int len);

t_philo	**create_philos(int nb_philo, t_env *env);

t_env	*create_env(int ac, char **av);

#endif
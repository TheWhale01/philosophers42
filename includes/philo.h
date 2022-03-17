/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:04:21 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/17 14:50:20 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <pthread.h>

# define EAT 0
# define DEAD 1
# define THINK 2
# define SLEEP 3
# define FORKS 4
# define FINISHED 5

typedef struct s_env
{
	int				nb_eat;
	int				nb_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	unsigned int	start_time;
	pthread_mutex_t	mutex_sleep;
	pthread_mutex_t	mutex_think;
	pthread_mutex_t	mutex_write;
}	t_env;

typedef struct s_philo
{
	int				id;
	int				state;
	int				last_meal;
	t_env			*env;
	pthread_t		thread;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	*mutex_next_fork;
}	t_philo;

int				ft_atoi(const char *nptr);

void			print_state(t_philo *philo);
void			exit_msg(int exit_code, char *str);

void			*live(void *ptr);
void			*free_philo(t_philo **tab, int len);

t_env			*create_env(int ac, char **av);

t_philo			**create_philos(int nb_philo, t_env *env);

unsigned int	get_ms(void);

#endif

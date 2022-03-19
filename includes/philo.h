/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:04:21 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/19 12:08:28 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <pthread.h>

# define EAT 0
# define DEAD 1
# define SLEEP 2
# define THINK 3
# define FORKS 4
# define FINISHED 5

typedef struct s_env
{
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	unsigned int	start_time;
	pthread_mutex_t	mutex_sleep;
	pthread_mutex_t	mutex_think;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_death;
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

typedef struct s_main
{
	int		died;
	int		nb_eat;
	int		nb_philos;
	t_philo	**philo_tab;
}	t_main;

int				ft_atoi(const char *nptr);

void			print_state(t_philo *philo);
void			create_philo(t_main *main_thread, t_env *env);
void			exit_msg(int exit_code, char *str, t_main *main_thread);

void			*live(void *ptr);
void			*free_philo(t_main *main_thread, int len);

t_env			*create_env(char **av);

t_main			*create_philos(int ac, char **av, t_env *env);

unsigned int	get_ms(void);

#endif

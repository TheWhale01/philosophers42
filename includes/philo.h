/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:04:21 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/31 10:32:55 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define INT_MAX 2147483647

typedef enum e_state
{
	EAT,
	DEAD,
	SLEEP,
	THINK,
	FORKS,
}	t_state;

typedef struct s_env
{
	int				died;
	int				limit_eat;
	int				nb_philos;
	int				start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
	pthread_mutex_t	actions;
	pthread_mutex_t	*forks;
}	t_env;

typedef struct s_philo
{
	int				id;
	int				state;
	int				nb_eat;
	t_env			*env;
	pthread_t		thread;
	unsigned int	last_meal;
}	t_philo;

int				ft_is_number(char *str);
int				check(int ac, char **av);
int				check_death(t_philo *philo);

void			launch(t_philo *philos);
void			ft_sleep(unsigned int ms);
void			philo_eat(t_philo *philo);
void			print_state(t_philo *philo);
void			philo_death(t_philo *philo);
void			philo_sleep_think(t_philo *philo, int state);

size_t			ft_strlen(const char *str);

t_philo			*init(int ac, char **av);

long long		ft_atoll(const char *nptr);

unsigned int	get_ms(void);

#endif

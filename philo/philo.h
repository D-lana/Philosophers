/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:00:50 by dlana             #+#    #+#             */
/*   Updated: 2022/01/22 14:59:28 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include "libft.h"

typedef enum e_value
{
	ERR_ARG,
	ERR_ARG_NUM,
	ERR_MEMORY,
	ERR_THREAD,
	ERR_MUTEX,
}				t_value;

typedef struct s_data {
	int				number_of_philos;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	int				time_must_eat;
	long long int	ref;
	int				death;
	long long int	cycle;
	int				i;
}				t_data;

typedef struct s_philo {
	pthread_t		body;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*end;
	long long int	last_eat;
	int				id;
	int				count_eat;
	t_data			*data;
}				t_philo;

typedef struct s_sim {
	t_philo			*philos;
	t_data			*data;
	pthread_t		monitor;
	pthread_mutex_t	*end;
}				t_sim;

int		ph_parser_philo(int argc, char **argv, t_sim *sim);
int		ph_check_digit(int argc, char **argv);
int		ph_init_data(t_sim *sim);
int		ph_create_forks(t_sim *sim);

int		ph_create_philo(t_sim *sim);
void	*ph_simulation(void *philo_v);
void	ph_print(struct timeval now, t_philo *philo, char *action);
int		ph_waiter(t_philo *philo);
void	ph_unlock_fork(t_philo *philo);

void	*ph_monitor(void *sim_v);
void	ph_init_last_eat(struct timeval now, t_sim *sim);
int		ph_monitor_cycle(struct timeval now, t_sim *sim, int i);
int		ph_count_eat(t_sim *sim);

int		ph_destroy_pthread_and_mutex(t_sim *sim);
int		ph_unlock_forks(t_sim *sim);

int		ph_error(int error);
int		ph_usleep(long int time);
void	ph_free(t_sim *sim);

#endif

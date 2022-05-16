/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:22:30 by dlana             #+#    #+#             */
/*   Updated: 2022/01/22 13:58:22 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include "libft.h"

typedef enum e_value
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
	BE_FULL,
	ERR_ARG,
	ERR_ARG_NUM,
	ERR_MEMORY,
	ERR_SEM,
	ERR_THREAD,
}				t_value;

typedef struct s_data
{
	int						number_of_philos;
	int						he_is_end_eat;
	int						time_must_eat;
	sem_t					*message;
	sem_t					*forks;
	sem_t					*death;
	sem_t					*waiters;
	long long int			t_start;
	long long int			time_to_die;
	long long int			time_to_eat;
	long long int			time_to_sleep;
	long long int			ref;
}							t_data;

typedef struct s_philo
{
	int						id;
	pid_t					pid;
	t_value					value;
	long long int			last_eat;
	int						time_must_eat;
	t_data					data;
}				t_philo;

typedef struct s_sim {
	t_philo			*philos;
	t_data			*data;
	pthread_t		wait_the_each_eat;
	pthread_mutex_t	*end;
}				t_sim;

int		ph_error(int error);
int		ph_usleep(long int time);
void	ph_kill_all(t_sim *sim);
void	ph_free(t_sim *sim);

int		ph_check_digit(int argc, char **argv);
int		ph_parser_philo(int argc, char **argv, t_sim *sim);
int		ph_init_data(t_sim *sim);
void	ph_init_semaphores(t_sim *sim);

void	ph_create_philo(t_sim *sim);
void	ph_simulation(t_philo *philo, t_sim *sim);
void	*ph_monitor(void *ph);
void	*ph_wait(void *in);

int		ph_do_action(t_sim *sim, t_philo *philo);
int		ph_eat(struct timeval now, t_data *data, t_philo *philo);
void	ph_print(struct timeval now, t_philo *philo, char *action);

#endif

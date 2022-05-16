/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_create_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:13:51 by dlana             #+#    #+#             */
/*   Updated: 2022/01/22 15:05:53 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ph_create_philo(t_sim *sim);
void	*ph_simulation(void *philo_v);
void	ph_print(struct timeval now, t_philo *philo, char *action);
int		ph_waiter(t_philo *philo);
void	ph_unlock_fork(t_philo *philo);

int	ph_create_philo(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->data->number_of_philos && sim->data->death == 0)
	{
		if (pthread_create(&sim->philos[i].body, NULL,
				&ph_simulation, &sim->philos[i]) != 0)
			return (ph_error(ERR_THREAD));
		i++;
	}
	if (pthread_create(&sim->monitor, NULL, &ph_monitor, sim) != 0)
		return (ph_error(ERR_THREAD));
	return (0);
}

void	*ph_simulation(void *philo_v)
{
	struct timeval	ref_point;
	struct timeval	now;
	t_philo			*philo;
	int				i;

	i = 0;
	philo = (t_philo *)philo_v;
	gettimeofday(&ref_point, NULL);
	philo->data->ref = (ref_point.tv_sec * 1000000 + ref_point.tv_usec);
	now = ref_point;
	while (philo->data->death == 0)
	{
		if (ph_waiter(philo) != 0)
			return (0);
		ph_print(now, philo, "is eating");
		ph_usleep(philo->data->time_to_eat);
		ph_unlock_fork(philo);
		ph_print(now, philo, "is sleeping");
		ph_usleep(philo->data->time_to_sleep);
		ph_print(now, philo, "is thinking");
		usleep(10);
		i++;
	}
	return (0);
}

int	ph_waiter(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (philo->data->death != 0)
		return (-1);
	if (philo->id % 2 != 0)
	{
		if (philo->data->number_of_philos % 2 != 0
			&& philo->id == philo->data->number_of_philos)
			usleep(700);
		pthread_mutex_lock(philo->left_fork);
		ph_print(now, philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		ph_print(now, philo, "has taken right fork");
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(philo->right_fork);
		ph_print(now, philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		ph_print(now, philo, "has taken left fork");
	}
	return (0);
}

void	ph_print(struct timeval now, t_philo *philo, char *action)
{
	long long int	t;

	pthread_mutex_lock(philo->end);
	if (philo->data->death != 1)
	{
		gettimeofday(&now, NULL);
		if (action[3] == 'e')
			philo->last_eat = (now.tv_sec * 1000000 + now.tv_usec) / 1000;
		t = ((now.tv_sec * 1000000 + now.tv_usec) - philo->data->ref) / 1000;
		printf("%lld Philo %d %s\n", t, philo->id, action);
	}
	pthread_mutex_unlock(philo->end);
}

void	ph_unlock_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->left_fork) != 0
		|| pthread_mutex_unlock(philo->right_fork) != 0)
		(ph_error(ERR_MUTEX));
	philo->count_eat++;
}

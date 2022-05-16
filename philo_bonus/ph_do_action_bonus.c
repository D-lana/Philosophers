/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_do_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:11:08 by dlana             #+#    #+#             */
/*   Updated: 2022/01/22 13:24:22 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int			ph_do_action(t_sim *sim, t_philo *philo);
int			ph_eat(struct timeval now, t_data *data, t_philo *philo);
void		ph_print(struct timeval now, t_philo *philo, char *action);

int	ph_do_action(t_sim *sim, t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (philo->value == EAT)
		return (ph_eat(now, sim->data, philo));
	else if (philo->value == SLEEP)
	{
		ph_print(now, philo, "is sleeping");
		ph_usleep(philo->data.time_to_sleep);
		return (THINK);
	}
	else if (philo->value == THINK)
	{
		ph_print(now, philo, "is thinking");
		philo->value = EAT;
		return (EAT);
	}
	return (DEAD);
}

int	ph_eat(struct timeval now, t_data *data, t_philo *philo)
{
	sem_wait(data->waiters);
	sem_wait(data->forks);
	ph_print(now, philo, "has taken a fork");
	sem_wait(data->forks);
	ph_print(now, philo, "has taken a fork");
	ph_print(now, philo, "is eating");
	philo->time_must_eat--;
	ph_usleep(philo->data.time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
	sem_post(data->waiters);
	if (philo->time_must_eat == 0)
		return (BE_FULL);
	return (SLEEP);
}

void	ph_print(struct timeval now, t_philo *philo, char *action)
{
	long long int	t;

	sem_wait(philo->data.message);
	gettimeofday(&now, NULL);
	if (action[3] == 'e')
		philo->last_eat = (now.tv_sec * 1000000 + now.tv_usec) / 1000;
	t = ((now.tv_sec * 1000000 + now.tv_usec) - philo->data.ref) / 1000;
	printf("%lld Philo %d %s\n", t, philo->id, action);
	sem_post(philo->data.message);
}

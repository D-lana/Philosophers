/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:16:10 by dlana             #+#    #+#             */
/*   Updated: 2022/01/20 14:18:12 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_monitor(void *sim_v);
void	ph_init_last_eat(struct timeval now, t_sim *sim);
int		ph_monitor_cycle(struct timeval now, t_sim *sim, int i);
int		ph_count_eat(t_sim *sim);

void	*ph_monitor(void *sim_v)
{
	struct timeval	now;
	int				i;
	t_sim			sim;

	i = 0;
	sim = *(t_sim *)sim_v;
	gettimeofday(&now, NULL);
	ph_init_last_eat(now, &sim);
	while (sim.data->death == 0)
	{
		gettimeofday(&now, NULL);
		while (i < sim.data->number_of_philos && sim.data->death == 0)
		{
			if (ph_monitor_cycle(now, &sim, i) != 0)
				return (0);
			i++;
		}
		i = 0;
		usleep(10);
	}
	return (0);
}

void	ph_init_last_eat(struct timeval now, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->data->number_of_philos)
	{
		sim->philos[i].last_eat = (now.tv_sec * 1000000 + now.tv_usec) / 1000;
		i++;
	}
}

int	ph_monitor_cycle(struct timeval now, t_sim *sim, int i)
{
	long long int	t;

	t = ((now.tv_sec * 1000000 + now.tv_usec) / 1000 - sim->philos[i].last_eat);
	if (t >= sim->data->time_to_die)
	{
		pthread_mutex_lock(sim->end);
		printf("%lld Philo %d died\n", (((now.tv_sec * 1000000 + now.tv_usec)
					- sim->data->ref) / 1000) + 1, i + 1);
		sim->data->death = 1;
		return (1);
	}
	if (sim->data->time_must_eat > 0)
	{
		if (ph_count_eat(sim) == 1)
			return (1);
	}
	return (0);
}

int	ph_count_eat(t_sim *sim)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sim->data->number_of_philos)
	{
		if (sim->philos[i].count_eat >= sim->data->time_must_eat)
			j++;
		i++;
	}
	if (j == sim->data->number_of_philos)
	{
		pthread_mutex_lock(sim->end);
		sim->data->death = 1;
		return (1);
	}
	return (0);
}

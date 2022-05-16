/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_create_philo_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:02:37 by dlana             #+#    #+#             */
/*   Updated: 2022/01/22 14:48:15 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_create_philo(t_sim *sim);
void	ph_simulation(t_philo *philo, t_sim *sim);
void	*ph_monitor(void *ph);
void	*ph_wait(void *sim_1);

void	ph_create_philo(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->data->number_of_philos)
	{
		sim->philos[i].pid = fork();
		if (0 == sim->philos[i].pid)
			ph_simulation(&sim->philos[i], sim);
		else
			i++;
	}
	if (pthread_create(&sim->wait_the_each_eat, NULL, ph_wait, sim) != 0)
		ph_error(ERR_THREAD);
	if (pthread_detach(sim->wait_the_each_eat) != 0)
		ph_error(ERR_THREAD);
	sem_wait(sim->data->death);
}

void	ph_simulation(t_philo *philo, t_sim *sim)
{
	pthread_t		thread;
	struct timeval	now;

	gettimeofday(&now, NULL);
	philo->last_eat = (now.tv_sec * 1000000 + now.tv_usec) / 1000;
	if (pthread_create(&thread, NULL, ph_monitor, philo) != 0)
		ph_error(ERR_THREAD);
	if (pthread_detach(thread) != 0)
		ph_error(ERR_THREAD);
	while (philo->value < DEAD)
	{
		philo->value = ph_do_action(sim, philo);
		if (philo->value == BE_FULL)
			break ;
		usleep(100);
	}
	exit(2);
}

void	*ph_monitor(void *philo_1)
{
	t_philo			*philo;
	long long int	t;
	struct timeval	now;

	philo = (t_philo *)philo_1;
	usleep(2500);
	while (philo->value != DEAD)
	{
		gettimeofday(&now, NULL);
		t = ((now.tv_sec * 1000000 + now.tv_usec) / 1000 - philo->last_eat);
		if (t >= philo->data.time_to_die)
		{
			philo->value = DEAD;
			sem_wait(philo->data.message);
			printf("%lld Philo %d died\n", (((now.tv_sec * 1000000 + now.tv_usec)
						- philo->data.ref) / 1000) + 1, philo->id);
			if (sem_post(philo->data.death) == -1)
				exit(ph_error(ERR_SEM));
			return (0);
		}
		usleep(500);
	}
	return (0);
}

void	*ph_wait(void *sim_1)
{
	int		value;
	pid_t	child;
	t_sim	*sim;

	sim = (t_sim *)sim_1;
	child = waitpid(0, &value, 0);
	value = WEXITSTATUS(value);
	if (value > 1 && sim->data->he_is_end_eat)
	{
		sim->data->he_is_end_eat--;
		ph_wait(sim);
	}
	else
	{
		if (sem_post(sim->data->death) == -1)
			exit(ph_error(ERR_SEM));
	}
	return (0);
}

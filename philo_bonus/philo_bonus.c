/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:25:49 by dlana             #+#    #+#             */
/*   Updated: 2022/01/20 15:25:49 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		ph_error(int error);
void	ph_kill_all(t_sim *sim);
void	ph_free(t_sim *sim);

int	ph_error(int error)
{
	if (error == ERR_ARG_NUM)
		write(2, "Error\nWrong arguments. Need 5 arguments.\n", 42);
	if (error == ERR_ARG)
		write(2, "Error\nWrong arguments!\n", 24);
	if (error == ERR_THREAD)
		write(2, "Error\nThread failed!\n", 22);
	if (error == ERR_MEMORY)
		write(2, "Error\nAllocation error!\n", 25);
	if (error == ERR_SEM)
		write(2, "Error\nSem failed!\n", 19);
	return (-1);
}

int	ph_usleep(long int time)
{
	struct timeval	t;
	struct timeval	start;

	gettimeofday(&start, NULL);
	gettimeofday(&t, NULL);
	usleep(time * 900);
	while (((t.tv_sec * 1000000 + t.tv_usec)
			- (start.tv_sec * 1000000 + start.tv_usec)) < time * 1000)
	{
		usleep(100);
		gettimeofday(&t, NULL);
	}
	return (0);
}

void	ph_kill_all(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->data->number_of_philos)
	{
		kill(sim->philos[i].pid, SIGTERM);
		i++;
	}
	sem_close(sim->data->forks);
	sem_close(sim->data->message);
	sem_close(sim->data->death);
	sem_close(sim->data->waiters);
}

void	ph_free(t_sim *sim)
{
	if (sim->philos)
		free(sim->philos);
	if (sim->data)
		free(sim->data);
}

int	main(int argc, char *argv[])
{
	t_sim	sim;

	if (argc < 5 || argc > 6)
		return (ph_error(ERR_ARG_NUM));
	ph_parser_philo(argc, argv, &sim);
	ph_init_data(&sim);
	ph_create_philo(&sim);
	ph_kill_all(&sim);
	ph_free(&sim);
	return (0);
}

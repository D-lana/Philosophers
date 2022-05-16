/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:29:05 by dlana             #+#    #+#             */
/*   Updated: 2022/01/22 15:01:32 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ph_error(int error);
int		ph_usleep(long int time);
void	ph_free(t_sim *sim);

int	ph_error(int error)
{
	if (error == ERR_ARG)
		write(2, "Error\nWrong arguments!\n", 24);
	if (error == ERR_ARG_NUM)
		write(2, "Error\nWrong arguments. Need 5 arguments.\n", 42);
	if (error == ERR_THREAD)
		write(2, "Error\nThread failed!\n", 32);
	if (error == ERR_MUTEX)
		write(2, "Error\nMutex failed!\n", 30);
	if (error == ERR_MEMORY)
		write(2, "Error\nAllocation error.\n", 25);
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

void	ph_free(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->data->number_of_philos)
	{
		if (sim->philos[i].right_fork)
			free(sim->philos[i].right_fork);
		i++;
	}
	if (sim->end)
		free(sim->end);
	if (sim->philos)
		free(sim->philos);
	if (sim->data)
		free(sim->data);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc < 5 || argc > 6)
		return (ph_error(ERR_ARG_NUM));
	if (ph_parser_philo(argc, argv, &sim) != 0)
		return (-1);
	if (ph_init_data(&sim) == -1)
		return (-1);
	if (ph_create_philo(&sim) == -1)
		return (-1);
	if (ph_destroy_pthread_and_mutex(&sim) == -1)
		return (-1);
	ph_free(&sim);
	return (0);
}

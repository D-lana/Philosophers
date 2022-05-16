/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parser_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:11:34 by dlana             #+#    #+#             */
/*   Updated: 2022/01/22 15:04:14 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ph_check_digit(int argc, char **argv);
int		ph_parser_philo(int argc, char **argv, t_sim *sim);
int		ph_init_data(t_sim *sim);
int		ph_create_forks(t_sim *sim);

int	ph_parser_philo(int argc, char **argv, t_sim *sim)
{
	sim->data = malloc(sizeof(t_data));
	if (sim->data == NULL)
		return (ph_error(ERR_MEMORY));
	if (ph_check_digit(argc, argv) == -1)
		return (ph_error(ERR_ARG));
	sim->data->time_must_eat = -2;
	sim->data->number_of_philos = ft_atoi(argv[1]);
	sim->data->time_to_die = ft_atoi(argv[2]);
	sim->data->time_to_eat = ft_atoi(argv[3]);
	sim->data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->data->time_must_eat = ft_atoi(argv[5]);
	if (sim->data->number_of_philos <= 0 || sim->data->time_to_die <= 0
		|| sim->data->time_to_eat <= 0 || sim->data->time_to_sleep < 0
		|| (sim->data->time_must_eat <= 0 && sim->data->time_must_eat != -2))
		return (ph_error(ERR_ARG));
	return (0);
}

int	ph_check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit((int) argv[i][j]) == 0)
				return (-1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	ph_init_data(t_sim *sim)
{
	int	i;

	i = 0;
	sim->data->death = 0;
	sim->philos = malloc(sizeof(t_philo) * (sim->data->number_of_philos));
	sim->end = malloc(sizeof(pthread_mutex_t));
	if (sim->philos == NULL || sim->end == NULL)
		return (ph_error(ERR_MEMORY));
	if (pthread_mutex_init(sim->end, NULL) != 0)
		return (ph_error(ERR_MUTEX));
	if (ph_create_forks(sim) == -1)
		return (-1);
	while (i < sim->data->number_of_philos)
	{
		sim->philos[i].end = sim->end;
		sim->philos[i].data = sim->data;
		sim->philos[i].id = i + 1;
		sim->philos[i].count_eat = 0;
		i++;
	}
	return (0);
}

int	ph_create_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->data->number_of_philos)
	{
		sim->philos[i].right_fork = malloc(sizeof(pthread_mutex_t) * 1);
		if (sim->philos[i].right_fork == NULL)
			return (ph_error(ERR_MEMORY));
		if (pthread_mutex_init(sim->philos[i].right_fork, NULL) != 0)
			return (ph_error(ERR_MUTEX));
		if (i > 0)
			sim->philos[i].left_fork = sim->philos[i - 1].right_fork;
		i++;
	}
	sim->philos[0].left_fork = sim->philos[i - 1].right_fork;
	return (0);
}

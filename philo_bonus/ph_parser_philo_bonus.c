/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parser_philo_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:26:49 by dlana             #+#    #+#             */
/*   Updated: 2022/01/22 14:44:53 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		ph_check_digit(int argc, char **argv);
int		ph_parser_philo(int argc, char **argv, t_sim *sim);
int		ph_init_data(t_sim *sim);
void	ph_init_semaphores(t_sim *sim);

int	ph_parser_philo(int argc, char **argv, t_sim *sim)
{
	sim->data = malloc(sizeof(t_data));
	if (sim->data == NULL)
		exit(ph_error(ERR_MEMORY));
	ph_check_digit(argc, argv);
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
		exit(ph_error(ERR_ARG));
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
				exit(ph_error(ERR_ARG));
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	ph_init_data(t_sim *sim)
{
	struct timeval	ref_p;
	int				i;

	i = 0;
	ph_init_semaphores(sim);
	sim->philos = malloc(sizeof(t_philo) * (sim->data->number_of_philos));
	if (sim->philos == NULL)
		exit(ph_error(ERR_MEMORY));
	sim->data->he_is_end_eat = sim->data->number_of_philos;
	gettimeofday(&ref_p, NULL);
	sim->data->ref = (ref_p.tv_sec * 1000000 + ref_p.tv_usec);
	while (i < sim->data->number_of_philos)
	{
		sim->philos[i].time_must_eat = sim->data->time_must_eat;
		sim->philos[i].value = EAT;
		sim->philos[i].id = i + 1;
		sim->philos[i].data = *sim->data;
		i++;
	}
	return (0);
}

void	ph_init_semaphores(t_sim *s)
{
	int	waiters;

	waiters = s->data->number_of_philos / 2;
	if (s->data->number_of_philos == 1)
		waiters = 1;
	sem_unlink("fork");
	s->data->forks = sem_open("fork", O_CREAT, 0777, s->data->number_of_philos);
	sem_unlink("mess");
	s->data->message = sem_open("mess", O_CREAT, 0777, 1);
	sem_unlink("wtr");
	s->data->waiters = sem_open("wtr", O_CREAT, 0777, waiters);
	sem_unlink("death");
	s->data->death = sem_open("death", O_CREAT, 0777, 0);
	if (s->data->death == SEM_FAILED || s->data->waiters == SEM_FAILED
		|| s->data->message == SEM_FAILED || s->data->forks == SEM_FAILED)
		exit(ph_error(ERR_SEM));
}

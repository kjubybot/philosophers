/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:35:34 by tmeizo            #+#    #+#             */
/*   Updated: 2021/01/05 12:35:40 by tmeizo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_sim *sim)
{
	int i;

	if (!(sim->philos = malloc(sizeof(t_philo) * sim->num_philos)))
		return (0);
	i = 0;
	while (i < sim->num_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].lfork = i;
		sim->philos[i].rfork = (i + 1) % sim->num_philos;
		sim->philos[i].state = STATE_THINKING;
		sim->philos[i].sim = sim;
		sim->philos[i].times_eaten = 0;
		i++;
	}
	return (1);
}

int	init_forks(t_sim *sim)
{
	int i;

	if (!(sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_philos)))
		return (0);
	i = 0;
	while (i < sim->num_philos)
		pthread_mutex_init(&sim->forks[i++], 0);
	return (1);
}

int	init_sim(t_sim *sim, int argc, char **argv)
{
	pthread_mutex_init(&sim->write_m, 0);
	pthread_mutex_init(&sim->end, 0);
	pthread_mutex_lock(&sim->end);
	sim->philos = 0;
	sim->forks = 0;
	sim->philos_full = 0;
	sim->num_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->times_eat = ft_atoi(argv[5]);
	else
		sim->times_eat = 0;
	if (sim->num_philos <= 1 || sim->num_philos > 200 || sim->time_to_die <= 0
	|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0 ||
	(argc == 6 && sim->times_eat <= 0))
		return (0);
	if (!init_philos(sim) || !init_forks(sim))
		return (0);
	return (1);
}

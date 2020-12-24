/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjubybot <kjubybot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:32:00 by kjubybot          #+#    #+#             */
/*   Updated: 2020/12/24 18:51:20 by kjubybot         ###   ########.fr       */
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
		sim->philos[i].state = STATE_THINKING;
		sim->philos[i].sim = sim;
		sim->philos[i].times_eaten = 0;
		i++;
	}
	return (1);
}

int	init_sim(t_sim *sim, int argc, char **argv)
{
	sim->philos = 0;
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
	sim->forks = sem_open("forks_sem", O_CREAT, 0660, sim->num_philos);
	sim->write_m = sem_open("write_sem", O_CREAT, 0660, 1);
	sim->end = sem_open("end_sem", O_CREAT, 0660, 0);
	if (!init_philos(sim) || !sim->forks || !sim->write_m || !sim->end)
		return (0);
	return (1);
}

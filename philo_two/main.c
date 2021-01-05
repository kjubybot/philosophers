/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:36:21 by tmeizo            #+#    #+#             */
/*   Updated: 2021/01/05 12:36:22 by tmeizo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *philo_v)
{
	t_philo			*philo;
	unsigned long	now;

	philo = (t_philo *)philo_v;
	while (!philo->sim->sim_ended)
	{
		now = get_time();
		if (philo->state != STATE_EATING && now >= philo->time_of_death &&
		!philo->sim->sim_ended)
		{
			philo->sim->sim_ended = 1;
			display_message(philo, " died\n");
			break ;
		}
		if (philo->sim->philos_full == philo->sim->num_philos)
		{
			philo->sim->sim_ended = 1;
			break ;
		}
		ft_usleep(500);
	}
	sem_post(philo->sim->end);
	return (0);
}

void	*routine(void *philo_v)
{
	t_philo			*philo;
	unsigned long	now;
	pthread_t		th;

	philo = (t_philo *)philo_v;
	if (philo->id % 2 == 0)
		ft_usleep(500);
	now = get_time();
	philo->time_of_death = now + philo->sim->time_to_die;
	pthread_create(&th, NULL, monitor, philo);
	pthread_detach(th);
	while (!philo->sim->sim_ended)
	{
		eat(philo);
		if (philo->sim->times_eat > 0 &&
			philo->times_eaten >= philo->sim->times_eat)
			return (0);
		sleep_and_think(philo);
	}
	return (0);
}

int		start_sim(t_sim *sim)
{
	pthread_t	th;
	int			i;

	sim->start_time = get_time();
	sim->sim_ended = 0;
	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_create(&th, NULL, routine, &sim->philos[i]))
			return (0);
		pthread_detach(th);
		i++;
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_sim	sim;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (!init_sim(&sim, argc, argv))
		return (free_and_exit(&sim, EXIT_FAILURE, "Initialization error\n"));
	if (!start_sim(&sim))
		return (free_and_exit(&sim, EXIT_FAILURE, "Error starting sim\n"));
	sem_wait(sim.end);
	sem_wait(sim.write_m);
	return (free_and_exit(&sim, EXIT_SUCCESS, "Simulation ended\n"));
}

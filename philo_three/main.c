/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjubybot <kjubybot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:31:11 by kjubybot          #+#    #+#             */
/*   Updated: 2020/12/28 16:08:12 by tmeizo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *philo_v)
{
	t_philo			*philo;
	unsigned long	now;

	philo = (t_philo *)philo_v;
	while (1)
	{
		now = get_time();
		if (philo->state != STATE_EATING && now >= philo->time_of_death)
		{
			display_message(philo, " died\n");
			exit(1);
		}
		usleep(100);
	}
}

void	routine(t_philo *philo)
{
	unsigned long	now;
	pthread_t		th;

	if (philo->id % 2 == 0)
		usleep(500);
	now = get_time();
	philo->time_of_death = now + philo->sim->time_to_die;
	pthread_create(&th, NULL, monitor, philo);
	pthread_detach(th);
	while (1)
	{
		eat(philo);
		if (philo->sim->times_eat > 0 &&
			philo->times_eaten >= philo->sim->times_eat)
			exit(0);
		sleep_and_think(philo);
	}
}

int		start_sim(t_sim *sim)
{
	pid_t	pid;
	int		i;

	sim->start_time = get_time();
	sim->sim_ended = 0;
	i = 0;
	while (i < sim->num_philos)
	{
		if ((pid = fork()) == 0)
			routine(&sim->philos[i]);
		else if (pid > 0)
			sim->philos[i].pid = pid;
		else
			return (0);
		i++;
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_sim	sim;
	int		status;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (!init_sim(&sim, argc, argv))
		return (free_and_exit(&sim, EXIT_FAILURE, "Initialization error\n"));
	if (!start_sim(&sim))
		return (free_and_exit(&sim, EXIT_FAILURE, "Error starting sim\n"));
	while (1)
	{
		waitpid(-1, &status, 0);
		if ((status & 0xff00) >> 8 == 0)
			sim.philos_full++;
		else if ((status & 0xff00) >> 8 == 1)
			break ;
		if (sim.philos_full == sim.num_philos)
			break ;
	}
	sem_wait(sim.write_m);
	return (free_and_exit(&sim, EXIT_SUCCESS, "Simulation ended\n"));
}

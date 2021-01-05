/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmeizo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:36:25 by tmeizo            #+#    #+#             */
/*   Updated: 2021/01/05 12:36:26 by tmeizo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_message(t_philo *philo, char *message)
{
	sem_wait(philo->sim->write_m);
	ft_putnbr(get_time() - philo->sim->start_time);
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, message, ft_strlen(message));
	sem_post(philo->sim->write_m);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->sim->forks);
	display_message(philo, " has taken a fork\n");
	sem_wait(philo->sim->forks);
	display_message(philo, " has taken a fork\n");
	display_message(philo, " is eating\n");
	philo->time_of_death = get_time() + philo->sim->time_to_die;
	philo->times_eaten++;
	if (philo->times_eaten == philo->sim->times_eat)
		philo->sim->philos_full++;
	philo->state = STATE_EATING;
	ft_usleep(philo->sim->time_to_eat * 1000);
	sem_post(philo->sim->forks);
	sem_post(philo->sim->forks);
}

void	sleep_and_think(t_philo *philo)
{
	philo->state = STATE_SLEEPING;
	display_message(philo, " is sleeping\n");
	ft_usleep(philo->sim->time_to_sleep * 1000);
	philo->state = STATE_THINKING;
	display_message(philo, " is thinking\n");
}

void	ft_usleep(useconds_t usec)
{
	unsigned long start;
	unsigned long msc;

	msc = usec / 1000;
	start = get_time();
	while (get_time() - start < msc)
		usleep(500);
}

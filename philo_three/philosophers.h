/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjubybot <kjubybot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:41:56 by kjubybot          #+#    #+#             */
/*   Updated: 2020/12/24 23:37:01 by kjubybot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define STATE_EATING 1
# define STATE_SLEEPING 2
# define STATE_THINKING 3

struct s_sim;

typedef struct	s_philo
{
	int				id;
	int				state;
	unsigned long	time_of_death;
	int				times_eaten;
	pid_t			pid;
	struct s_sim	*sim;
}				t_philo;

typedef struct	s_sim
{
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*write_m;
	int				num_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	start_time;
	int				times_eat;
	int				philos_full;
	int				sim_ended;
}				t_sim;

int				init_sim(t_sim *sim, int argc, char **argv);

void			display_message(t_philo *philo, char *message);

void			eat(t_philo *philo);

void			sleep_and_think(t_philo *philo);

int				ft_atoi(char *s);

void			ft_putnbr(unsigned long n);

int				ft_strlen(char *s);

int				free_and_exit(t_sim *sim, int status, char *message);

unsigned long	get_time(void);

#endif

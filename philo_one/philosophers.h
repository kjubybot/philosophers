/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjubybot <kjubybot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:41:56 by kjubybot          #+#    #+#             */
/*   Updated: 2020/12/24 22:42:14 by kjubybot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define STATE_EATING 1
# define STATE_SLEEPING 2
# define STATE_THINKING 3

struct s_sim;

typedef struct	s_philo
{
	int				id;
	int				lfork;
	int				rfork;
	int				state;
	unsigned long	time_of_death;
	int				times_eaten;
	pthread_t		th;
	struct s_sim	*sim;
}				t_philo;

typedef struct	s_sim
{
	t_philo			*philos;
	pthread_mutex_t	end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_m;
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

void			ft_usleep(useconds_t usec);

#endif

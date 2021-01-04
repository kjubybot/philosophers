/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjubybot <kjubybot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:32:50 by kjubybot          #+#    #+#             */
/*   Updated: 2020/12/24 18:58:50 by kjubybot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				ft_atoi(char *s)
{
	int	res;

	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			return (0);
		s++;
	}
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	return (res);
}

void			ft_putnbr(unsigned long n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
	}
	else
		c = n + '0';
	write(1, &c, 1);
}

int				free_and_exit(t_sim *sim, int status, char *message)
{
	sem_unlink("end_sem");
	sem_unlink("forks_sem");
	if (sim->philos)
		free(sim->philos);
	write(1, message, ft_strlen(message));
	sem_unlink("write_sem");
	return (status);
}

int				ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

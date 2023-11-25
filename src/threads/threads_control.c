/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:12:13 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/11/25 02:15:37 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	change_fork_value(pthread_mutex_t	*mutex_fork, int *fork, int state)
{
	pthread_mutex_lock(mutex_fork);
	*fork = state;
	pthread_mutex_unlock(mutex_fork);
}

int	try_to_take_fork(pthread_mutex_t	*mutex_fork, int *fork)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex_fork);
	if (*fork == 0)
	{
		ret = 1;
		*fork = 1;
	}
	pthread_mutex_unlock(mutex_fork);
	return (ret);
}

int	eating(t_2link_circ_list *vars)
{
	struct timeval				t_eat;
	long int					time_alive;

	// pthread_mutex_lock(&(vars->mutex.t_start_eating));
	// gettimeofday(&(vars->start_eating), NULL);
	// pthread_mutex_unlock(&(vars->mutex.t_start_eating));
	while (1)
	{
		if (try_to_take_fork(&(vars->next->mutex.fork), \
			&(vars->next->id_fork.fork)))
		{
			if (try_to_take_fork(&(vars->mutex.fork), \
				&(vars->id_fork.fork)))
			{
				pthread_mutex_lock(&(vars->mutex.print));
				gettimeofday(&(t_eat), NULL);
				pthread_mutex_lock(&(vars->mutex.t_born_philo));
				time_alive = ((t_eat.tv_sec - vars->born_philo.tv_sec) * 1000 + (t_eat.tv_usec - vars->born_philo.tv_usec) / 1000);
				pthread_mutex_unlock(&(vars->mutex.t_born_philo));
				printf("%s[%ld ms] %d is eating%s\n", BLUE, time_alive, vars->id_fork.id, FN);
				pthread_mutex_unlock(&(vars->mutex.print));
				pthread_mutex_lock(&(vars->mutex.t_start_eating));
				gettimeofday(&(vars->start_eating), NULL);
				pthread_mutex_unlock(&(vars->mutex.t_start_eating));
				if (ft_usleep(vars->routine.time_to_eat * 1000, vars))
					return (1);
				change_fork_value(&(vars->next->mutex.fork), \
					&(vars->next->id_fork.fork), 0);
				change_fork_value(&(vars->mutex.fork), \
					&(vars->id_fork.fork), 0);
				break ;
			}
			else
				change_fork_value(&(vars->next->mutex.fork), \
					&(vars->next->id_fork.fork), 0);
		}
		ft_usleep(500, vars);
	}
	return (0);
}

int	sleeping(t_2link_circ_list *vars)
{
	struct timeval				t_sleep;
	long int					sleep;

	pthread_mutex_lock(&(vars->mutex.print));
	gettimeofday(&(t_sleep), NULL);
	pthread_mutex_lock(&(vars->mutex.t_born_philo));
	sleep = ((t_sleep.tv_sec - vars->born_philo.tv_sec) * 1000 + (t_sleep.tv_usec - vars->born_philo.tv_usec) / 1000);
	pthread_mutex_unlock(&(vars->mutex.t_born_philo));
	printf("%s[%ld ms] %d is sleeping %s\n", GREEN, sleep, vars->id_fork.id, FN);
	pthread_mutex_unlock(&(vars->mutex.print));
	if (ft_usleep(vars->routine.time_to_sleep * 1000, vars))
		return (1);
	return (0);
}

void	thinking(t_2link_circ_list *vars)
{
	struct timeval				t_think;

	pthread_mutex_lock(&(vars->mutex.print));
	gettimeofday(&(t_think), NULL);
	printf("%s[%ld ms] %d is thinking %s\n", PINK, ((t_think.tv_sec - vars->born_philo.tv_sec) * 1000 + (t_think.tv_usec - vars->born_philo.tv_usec) / 1000), vars->id_fork.id, FN);
	pthread_mutex_unlock(&(vars->mutex.print));
}

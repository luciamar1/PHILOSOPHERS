/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:12:13 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/10/26 21:21:07 by lucia-ma         ###   ########.fr       */
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

void	eating(t_2link_circ_list *vars)
{
	while (1)
	{
		if (try_to_take_fork(&(vars->next->mutex.fork), \
			&(vars->next->id_fork.fork)))
		{
			if (try_to_take_fork(&(vars->mutex.fork), \
				&(vars->id_fork.fork)))
			{
				ft_usleep(vars->routine.time_to_eat);
				pthread_mutex_lock(&(vars->mutex.print));
				gettimeofday(&(vars->t_eat), NULL);
				printf("%s[%ld ms] %d is eating%s\n", BLUE, ((vars->t_eat.tv_sec - vars->born_philo.tv_sec) * 1000 + (vars->t_eat.tv_usec - vars->born_philo.tv_usec) / 1000), vars->id_fork.id, FN);
				pthread_mutex_unlock(&(vars->mutex.print));
				//change_2fork_values(vars, 0);
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
		ft_usleep(500);
	}
}

void	sleeping(t_2link_circ_list *vars)
{
	ft_usleep(vars->routine.time_to_sleep);
	gettimeofday(&(vars->t_sleep), NULL);
	pthread_mutex_lock(&(vars->mutex.print));
	printf("%s[%ld ms] %d is sleeping %s\n", GREEN, ((vars->t_sleep.tv_sec - vars->born_philo.tv_sec) * 1000 + (vars->t_sleep.tv_usec - vars->born_philo.tv_usec) / 1000), vars->id_fork.id, FN);
	pthread_mutex_unlock(&(vars->mutex.print));
}

void	thinking(t_2link_circ_list *vars)
{
	gettimeofday(&(vars->t_think), NULL);
	pthread_mutex_lock(&(vars->mutex.print));
	printf("%s[%ld ms] %d is thinking %s\n", PINK, ((vars->t_think.tv_sec - vars->born_philo.tv_sec) * 1000 + (vars->t_think.tv_usec - vars->born_philo.tv_usec) / 1000), vars->id_fork.id, FN);
	pthread_mutex_unlock(&(vars->mutex.print));
}

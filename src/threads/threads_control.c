/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:12:13 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/11/27 19:06:56 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	eating_aux(t_2link_circ_list *vars)
{
	print_status(vars, 1);
	pthread_mutex_lock(&(vars->mutex.t_start_eating));
	gettimeofday(&(vars->start_eating), NULL);
	pthread_mutex_unlock(&(vars->mutex.t_start_eating));
	if (ft_usleep(vars->routine.time_to_eat * 1000, vars))
		return (1);
	else
		return (0);
}

int	eating(t_2link_circ_list *vars)
{
	while (1)
	{
		if (im_dead_(vars))
			return (1);
		if (try_to_take_fork(&(vars->next->mutex.fork), \
			&(vars->next->id_fork.fork)))
		{
			if (try_to_take_fork(&(vars->mutex.fork), \
				&(vars->id_fork.fork)))
			{
				if (eating_aux(vars))
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
	if (im_dead_(vars))
		return (1);
	print_status(vars, 3);
	if (ft_usleep(vars->routine.time_to_sleep * 1000, vars))
		return (1);
	return (0);
}

void	thinking(t_2link_circ_list *vars)
{
	print_status(vars, 2);
}

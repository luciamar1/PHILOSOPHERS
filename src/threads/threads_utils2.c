/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:11:35 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/12/11 22:43:51 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_finish(t_2link_circ_list *vars)
{
	int	counter;
	int	n_philo_finished;
	int aux = 0;

	n_philo_finished = 0;
	counter = vars->routine.n_philos;
	while (counter)
	{
		pthread_mutex_lock(&(vars->mutex.threads_ended));
		if (vars->threads_ended == 1)
		{
			n_philo_finished ++;
			aux ++;

		}
		pthread_mutex_unlock(&(vars->mutex.threads_ended));
		vars = vars->next;
		counter --;
	}
	if (n_philo_finished == vars->routine.n_philos)
	{
		return (1);
	}
	return (0);
}

void	calculate_thread_death(t_2link_circ_list *vars)
{
	long long		time_elapsed;
	struct timeval	end;

	while (1)
	{
		gettimeofday(&end, NULL);
		pthread_mutex_lock(&(vars->mutex.t_start_eating));
		time_elapsed = ((end.tv_sec - vars->start_eating.tv_sec) * 1000) + \
			((end.tv_usec - vars->start_eating.tv_usec) / 1000);
		pthread_mutex_unlock(&(vars->mutex.t_start_eating));
		if (check_if_finish(vars))
			break ;
		if ((long long) vars->routine.time_to_die < time_elapsed)
		{
			if (check_if_finish(vars))
				break ;
			pthread_mutex_lock((vars->mutex_im_dead));
			if (*(vars->dead) == 0)
				*(vars->dead) = 1;
			pthread_mutex_unlock((vars->mutex_im_dead));
			gettimeofday(&end, NULL);
			print_status(vars, 4);
			break ;
		}
		vars = vars->next;
		ft_usleep(200, vars);
	}
}

int	im_dead_(t_2link_circ_list *vars)
{
	pthread_mutex_lock((vars->mutex_im_dead));
	if (*(vars->dead) == 1)
	{
		pthread_mutex_unlock((vars->mutex_im_dead));
		return (1);
	}
	pthread_mutex_unlock((vars->mutex_im_dead));
	return (0);
}

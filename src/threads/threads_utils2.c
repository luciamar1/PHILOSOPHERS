/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:11:35 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/12/19 20:23:48 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_finish(t_2link_circ_list *vars)
{
	int	counter;
	int	n_philo_finished;

	if (vars->routine.number_of_times != -1 && vars->routine.n_philos > 1)
	{
		n_philo_finished = 0;
		counter = vars->routine.n_philos;
		while (counter)
		{
			pthread_mutex_lock(&(vars->mutex.threads_ended));
			if (vars->threads_ended <= 0)
				n_philo_finished ++;
			pthread_mutex_unlock(&(vars->mutex.threads_ended));
			vars = vars->next;
			counter --;
		}
		if (n_philo_finished == vars->routine.n_philos)
		{
			return (n_philo_finished);
		}
		return (n_philo_finished);
	}
	else
		return (-1);
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
		if (check_if_finish(vars) == vars->routine.n_philos)
			break ;
		if ((long long) vars->routine.time_to_die < time_elapsed)
		{
			pthread_mutex_lock((vars->mutex_im_dead));
			if (*(vars->dead) == 0)
				*(vars->dead) = 1;
			pthread_mutex_unlock((vars->mutex_im_dead));
			gettimeofday(&end, NULL);
			print_status(vars, 4);
			break ;
		}
		vars = vars->next;
		ft_usleep(1000, vars);
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

void	clear_philo(t_2link_circ_list **vars, pthread_t **id_threads)
{
	pthread_mutex_destroy((*vars)->mutex_im_dead);
	pthread_mutex_destroy((*vars)->mutex_print);
	pthread_mutex_destroy((*vars)->mutex_no_print);
	pthread_mutex_destroy((*vars)->mutex_all_sit);
	if ((*vars)->dead)
		free((*vars)->dead);
	if ((*vars)->all_sit)
		free((*vars)->all_sit);
	if ((*vars)->no_print)
		free((*vars)->no_print);
	if ((*vars)->mutex_im_dead)
		free((*vars)->mutex_im_dead);
	if ((*vars)->mutex_print)
		free((*vars)->mutex_print);
	if ((*vars)->mutex_no_print)
		free((*vars)->mutex_no_print);
	if ((*vars)->mutex_all_sit)
		free((*vars)->mutex_all_sit);
	mutex_destroy(*vars);
	if (*vars)
		clear_2link_circ_list(vars);
	if (*id_threads)
		free(*id_threads);
}

void	wait_to_sit(t_2link_circ_list *vars)
{
	while (1)
	{
		pthread_mutex_lock(vars->mutex_all_sit);
		if ((*(vars->all_sit)) >= vars->routine.n_philos)
		{
			pthread_mutex_unlock((vars->mutex_all_sit));
			break ;
		}
		pthread_mutex_unlock((vars->mutex_all_sit));
	}
}

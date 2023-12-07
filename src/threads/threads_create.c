/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:08:33 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/12/07 23:25:38 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	actions(t_2link_circ_list *vars)
{
	if (im_dead_(vars))
		return (1);
	pthread_mutex_lock(&(vars->mutex.id));
	if (is_impar(vars->id_fork.id))
	{
		if (eating_impar(vars))
		{
			pthread_mutex_unlock(&(vars->mutex.id));
			return (1);
		}
		pthread_mutex_unlock(&(vars->mutex.id));
	}
	else
	{
		if (eating_par(vars))
		{
			return(1);
		}
	}
	if (im_dead_(vars))
		return (1);
	if (sleeping(vars))
		return (1);
	if (im_dead_(vars))
		return (1);
	thinking(vars);
	return (0);
}

void	number_actions(t_2link_circ_list *vars)
{
	int	n_times;
	int counter = 0;

	pthread_mutex_lock(vars->mutex_all_sit);
	*(vars->all_sit) = (*(vars->all_sit)) + 1;
	pthread_mutex_unlock(vars->mutex_all_sit);
	if (vars->routine.number_of_times >= 0)
	{
		n_times = vars->routine.number_of_times;
		while (n_times)
		{
			if (actions(vars))
				break ;
			printf("accion == %d\n", counter);
			n_times --;
			counter ++;
		}
	}
	else
	{
		while (1)
			if (actions(vars))
				break ;
	}
	pthread_mutex_lock(&(vars->mutex.threads_ended));
	vars->threads_ended ++;
	pthread_mutex_unlock(&(vars->mutex.threads_ended));
}

void	*f_hilo(void *args)
{
	t_2link_circ_list	*vars;

	vars = (t_2link_circ_list *) args;
	pthread_mutex_lock(&(vars->mutex.t_start_eating));
	gettimeofday(&(vars->start_eating), NULL);
	pthread_mutex_unlock(&(vars->mutex.t_start_eating));
	pthread_mutex_lock(&(vars->next->mutex.id));
	if (is_impar(vars->id_fork.id))
	{
		ft_usleep(200, vars);
	}
	pthread_mutex_unlock(&(vars->next->mutex.id));
	gettimeofday(&(vars->born_philo), NULL);
	number_actions(vars);
	return (NULL);
}

void	wait_to_sit(t_2link_circ_list *vars)
{
	while (1)
	{
		pthread_mutex_lock((vars->mutex_all_sit));
		if ((*(vars->all_sit)) >= vars->routine.n_philos)
		{
			pthread_mutex_unlock((vars->mutex_all_sit));
			break ;
		}
		pthread_mutex_unlock((vars->mutex_all_sit));
	}
}

int	create_threads(int n_threads, t_2link_circ_list *vars, pthread_t *threads)
{
	int					counter;
	int					aux;
	int					espera;

	aux = ((counter = 0), n_threads);
	while (aux)
	{
		if (pthread_create(&threads[counter], NULL, f_hilo, vars))
			return (perror("pthread_create fail"), 1);
		vars = vars->next;
		aux --;
		counter ++;
	}
	wait_to_sit(vars);
	calculate_thread_death(vars);
	counter = 0;
	while (n_threads)
	{
		espera = pthread_join(threads[counter], NULL);
		if (espera)
			return (perror("wait pthread fail"), 1);
		n_threads --;
		counter ++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:09:33 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/12/12 21:42:59 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_2link_circ_list *list)
{
	if (pthread_mutex_init(&(list->mutex.fork), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.id), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.threads_ended), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.t_start_eating), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.im_arriving), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	return (0);
}

void	mutex_destroy(t_2link_circ_list *list)
{
	int	num;

	num = list->routine.n_philos;
	while (num)
	{
		pthread_mutex_destroy(&(list->mutex.fork));
		pthread_mutex_destroy(&(list->mutex.id));
		pthread_mutex_destroy(&(list->mutex.threads_ended));
		pthread_mutex_destroy(&(list->mutex.t_start_eating));
		pthread_mutex_destroy(&(list->mutex.im_arriving));
		list = list->next;
		num --;
	}
}

void	change_fork_value(pthread_mutex_t	*mutex_fork, int *fork, int state)
{
	pthread_mutex_lock(mutex_fork);
	*fork = state;
	pthread_mutex_unlock(mutex_fork);
}

/// 1 = eat   2 = think     3 = sleep    4 = die

void	print_status(t_2link_circ_list *vars, int action)
{
	struct timeval	actual_time;
	long int		t;

	gettimeofday(&(actual_time), NULL);
	t = ((actual_time.tv_sec - vars->born_philo.tv_sec) * 1000 + \
		(actual_time.tv_usec - vars->born_philo.tv_usec) / 1000);
	pthread_mutex_lock(vars->mutex_print);
	if (action == 1)
	{
		printf("%s[%ld ms] %d has taken a fork%s\n", YELLOW, t, \
			vars->id_fork.id, FN);
		printf("%s[%ld ms] %d has taken a fork%s\n", YELLOW, t, \
			vars->id_fork.id, FN);
		printf("%s[%ld ms] %d is eating%s\n", BLUE, t, vars->id_fork.id, FN);
	}
	if (action == 2)
		printf("%s[%ld ms] %d is thinking%s\n", PINK, t, vars->id_fork.id, FN);
	if (action == 3)
		printf("%s[%ld ms] %d is sleeping%s\n", GREEN, t, vars->id_fork.id, FN);
	if (action == 4)
		printf("%s[%ld ms] %d is dead %s\n", RED, t, vars->id_fork.id, FN);
	pthread_mutex_unlock((vars->mutex_print));
}

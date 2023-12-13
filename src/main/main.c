/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:49:37 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/12/13 14:00:44 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_philo(t_2link_circ_list **vars, pthread_t **id_threads)
{
	pthread_mutex_destroy((*vars)->mutex_im_dead);
	pthread_mutex_destroy((*vars)->mutex_print);
	pthread_mutex_destroy((*vars)->mutex_all_sit);
	free((*vars)->dead);
	if (*vars)
		clear_2link_circ_list(vars);
	if (*id_threads)
		free(*id_threads);
}

int	verify_args(int argc, char **argv)
{
	if (argc != 4 && argc != 5)
	{
		write(2, "the number of arguments is incorrect\n", 38);
		return (1);
	}
	while (*argv)
	{
		if (ft_arr_isdigit(*argv) == 0)
		{
			write(2, "the type of arguments are incorrect\n", 37);
			return (1);
		}
		argv++;
	}
	return (0);
}

/* ************************************************************************** */
int	create_routine_struct(int argc, char **argv, t_philo_routine *rou, int n_ph)
{
	int				err;

	err = 0;
	(*rou).n_philos = n_ph;
	(*rou).time_to_die = ft_atoi_chetao(argv[1], &err);
	if (err)
		return (1);
	(*rou).time_to_eat = ft_atoi_chetao(argv[2], &err);
	if (err)
		return (1);
	(*rou).time_to_sleep = ft_atoi_chetao(argv[3], &err);
	if (err)
		return (1);
	if (argc == 5)
		(*rou).number_of_times = ft_atoi_chetao(argv[4], &err);
	else
		(*rou).number_of_times = -1;
	return (0);
}

int	create_list_philo(int argc, char **argv, t_2link_circ_list **lista)
{
	int					err;
	int					counter;
	int					n_philo;
	t_philo_routine		routine;
	t_statement_var		statement_var;

	statement_var.all_sit = ((statement_var.dead = malloc(4)), malloc(4));
	if (!statement_var.dead || !statement_var.all_sit)
		return (1);
	*statement_var.all_sit = ((*statement_var.dead = 0), 0);
	err = 0;
	n_philo = ft_atoi_chetao(argv[0], &err);
	if (err)
		return (1);
	if (create_routine_struct(argc, argv, &routine, n_philo))
		return (1);
	counter = 0;
	while (n_philo)
	{
		if (create_2link_circlist(lista, create_dict_int(counter), \
			routine, statement_var))
			return (perror("create_list_philo: "), 1);
		counter = ((n_philo --), counter + 1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_2link_circ_list	*list;
	pthread_t			*id_threads;
	int					num_threads;
	int					err;

	list = NULL;
	if (verify_args(--argc, ++argv) || create_list_philo(argc, argv, &list))
		return (1);
	if (!list)
		return (printf("imposible to start the project\n"), 1);
	err = 0;
	num_threads = ft_atoi_chetao(argv[0], &err);
	if (err)
		return (clear_philo(&list, &id_threads), 1);
	id_threads = malloc(sizeof(pthread_t) * num_threads);
	if (!id_threads)
		return (clear_philo(&list, &id_threads), perror(""), 1);
	if (create_threads(num_threads, list, id_threads))
	{
		mutex_destroy(list);
		return (clear_philo(&list, &id_threads), 1);
	}
	mutex_destroy(list);
	clear_philo(&list, &id_threads);
	return (0);
}

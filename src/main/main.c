/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:49:37 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/12/19 20:10:32 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    leaks(void)
{
    system("leaks -q philo");
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

int	aux_create_list(t_statement_var *vars)
{
	if (!vars->dead || !vars->all_sit || !vars->no_print)
	{
		if (vars->dead)
			free(vars->dead);
		if (vars->no_print)
			free(vars->no_print);
		if (vars->all_sit)
			free(vars->all_sit);
		return (1);
	}
	*vars->all_sit = ((*vars->dead = 0), 0);
	*vars->no_print = 0;
	return (0);
}

int	create_list_philo(int argc, char **argv, t_2link_circ_list **lista)
{
	int					err;
	int					counter;
	int					n_philo;
	t_philo_routine		routine;
	t_statement_var		stat;

	stat.all_sit = ((stat.dead = malloc(4)), \
		(stat.no_print = malloc(4)), malloc(4));
	if (aux_create_list(&stat))
		return (1);
	err = 0;
	n_philo = ft_atoi_chetao(argv[0], &err);
	if (err)
		return (free(stat.dead), free(stat.all_sit), free(stat.no_print), 1);
	if (create_routine_struct(argc, argv, &routine, n_philo))
		return (free(stat.dead), free(stat.all_sit), free(stat.no_print), 1);
	counter = 0;
	while (n_philo)
	{
		if (create_2link_circlist(lista, create_dict_int(counter), \
			routine, stat))
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
		return (clear_philo(&list, &id_threads), 1);
	}
	clear_philo(&list, &id_threads);
	atexit(leaks);
	return (0);
}

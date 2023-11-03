#include "philo.h"

void	clear_philo(t_2link_circ_list **vars, pthread_t **id_threads)
{
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
		if (ft_arr_isdigit(*argv) == 1)
		{
			write(2, "the type of arguments are incorrect\n", 37);
			return (1);
		}
		argv ++;
	}
	return (0);
}

int	create_routine_struct(int argc, char **argv, t_philo_routine *routine, int n_philos)
{
	int				err;

	err = 0;
	(*routine).n_philos = n_philos;
	(*routine).time_to_die = ft_atoi_chetao(argv[1], &err);
	if (err)
		return (1);
	(*routine).time_to_eat = ft_atoi_chetao(argv[2], &err);
	if (err)
		return (1);
	(*routine).time_to_sleep = ft_atoi_chetao(argv[3], &err);
	if (err)
		return (1);
	if (argc == 5)
		(*routine).number_of_times = ft_atoi_chetao(argv[4], &err);
	else 
		(*routine).number_of_times = 0;
	return (0);
}

int create_list_philo(int argc, char **argv, t_2link_circ_list **lista)
{
	int					err;
	int					counter;
	int					n_philo;
	t_philo_routine		routine;
	int					*dead;

	dead = malloc(4);
	if (!dead)
		return 1;
	*dead = 0;
	err = 0;
	n_philo = ft_atoi_chetao(argv[0], &err);
	if (err)
		return (1);
	if (create_routine_struct(argc, argv, &routine, n_philo))
		return (1);
	counter = 0;
	while (n_philo)
	{
		if (create_2link_circlist(lista, create_dict_int(counter), routine, dead))
			return (perror("create_list_philo: "), 1);
		n_philo --;
		counter ++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_2link_circ_list	*list;
	pthread_t			*id_threads;
	int					num_threads;
	int					err;

	if (verify_args(--argc, ++argv))
		return (1);
	if (create_list_philo(argc, argv, &list))
		return (1);

	// int i = 0;
	// list->dead = &i;
	// printf("bbbbb == %d\n", (int)(*(list->dead)));
	
	// printf_dlist_ind(list);
	// printf("aaaaa == %p\n", list->dead);
	// printf("aaaaa == %p\n", list->next->dead);
	// 	sleep(5);
	if (!list)
		printf("NO HAY LISTA\n");
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

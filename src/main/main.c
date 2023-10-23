#include "philo.h"

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

int	create_routine_struct(int argc, char **argv, t_philo_routine *routine)
{
	int				err;

	err = 0;
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
	return (0);
}

t_2link_circ_list	*create_list_philo(int argc, char **argv)
{
	t_2link_circ_list	*lista;
	int					err;
	int					counter;
	int					n_philo;
	t_philo_routine		routine;

	lista = NULL;
	err = 0;
	n_philo = ft_atoi_chetao(argv[0], &err);
	if (err)
		return (NULL);
	if (create_routine_struct(argc, argv, &routine))
		return (NULL);
	counter = 0;
	while (n_philo)
	{
		if (create_2link_circlist(&lista, create_dict_int(counter), routine))
			return (perror("create_list_philo: "), NULL);
		n_philo --;
		counter ++;
	}
	return (lista);
}

void	clear_philo(t_2link_circ_list **vars, pthread_t **id_threads)
{
	if (*vars)
		clear_2link_circ_list(vars);
	if (*id_threads)
		free(*id_threads);
}

int	main(int argc, char **argv)
{
	t_2link_circ_list	*list;
	pthread_t			*id_threads;
	int					num_threads;
	int					err;

	argv ++;
	if (verify_args(argc - 1, (argv)))
		return (1);
	list = create_list_philo(argc - 1, argv);
	if (!list)
		printf("NO HAY LISTA\n");
	err = 0;
	num_threads = ft_atoi_chetao(argv[0], &err);
	if (err)
		return (clear_philo(&list, &id_threads), 1);
	id_threads = malloc(sizeof(pthread_t) * num_threads);
	if (!id_threads)
		return (clear_philo(&list, &id_threads), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.fork), NULL))
		return (clear_philo(&list, &id_threads), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.print), NULL))
		return (clear_philo(&list, &id_threads), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.id), NULL))
		return (clear_philo(&list, &id_threads), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.eat), NULL))
		return (clear_philo(&list, &id_threads), perror(""), 1);
	if (create_threads(num_threads, list, id_threads))
	{
		pthread_mutex_destroy(&(list->mutex.fork));
		pthread_mutex_destroy(&(list->mutex.print));
		return (clear_philo(&list, &id_threads), 1);
	}
	pthread_mutex_destroy(&(list->mutex.fork));
	pthread_mutex_destroy(&(list->mutex.print));
	pthread_mutex_destroy(&(list->mutex.id));
	pthread_mutex_destroy(&(list->mutex.eat));

	clear_philo(&list, &id_threads);
	return (0);
}

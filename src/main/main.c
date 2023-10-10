#include "philo.h"

// void *f_hilo(void *args) 
// {
// 	t_philosophers	*vars;

// 	vars = (t_philosophers *) args;
// 	printf("%d, %d, %d\n", vars->time_to_die, vars->time_to_eat, vars->time_to_sleep);
// 	printf("hola luci te quiero =)\n\n");
// 	return (NULL);
// }

// int	verify_args(int argc, char **argv)
// {
// 	if (argc != 3 && argc != 4)
// 	{
// 		write(2, "the number of arguments is incorrect\n", 38);
// 		return (1);
// 	}
// 	while (*argv)
// 	{
// 		if (ft_arr_isdigit(*argv) == 1)
// 		{
// 			write(2, "the type of arguments are incorrect\n", 37);
// 			return (1);
// 		}
// 		argv ++;
// 	}
// 	return (0);
// }

// int	create_philo_struct(int argc, char **argv, t_philosophers	*vars)
// {
// 	int				err;
// 	t_ldictionary	*id_fork;
// 	int				n_threads;

// 	err = 0;
// 	(*vars).time_to_die = ft_atoi_chetao(argv[1], &err);
// 	if (err)
// 		return (1);
// 	(*vars).time_to_eat = ft_atoi_chetao(argv[2], &err);
// 	if (err)
// 		return (1);
// 	if (argc == 4)
// 		(*vars).time_to_sleep = ft_atoi_chetao(argv[3], &err);
// 	if (err)
// 		return (1);
// 	n_threads = ft_atoi_chetao(argv[0], &err);
// 	id_fork = (void *)malloc(sizeof(t_ldictionary));
// 	while (n_threads --)
// 	{
// 		l_dictionary_add_back(&id_fork, l_dictionary_new((pthread_t )-2, 0));
// 	}
// 	return (0);
// }


// int	create_threads(int threads, t_philosophers	*vars)
// {
// 	int				creacion;
// 	int				counter;
// 	int				aux;
// 	int				espera;

// 	aux = threads;
// 	counter = 0;
// 	while (threads)
// 	{
// 		creacion = pthread_create(&(vars->id_fork->key), NULL, f_hilo, vars);
// 		if (creacion)
// 			return (write(2, "pthread_create fail\n", 21), 1);
// 		counter ++;
// 		threads --;
// 	}
// 	while (aux --)
// 	{
// 		espera = pthread_join(vars->id_fork->key, NULL);
// 		if (espera)
// 			return (write(2, "wait pthread fail\n", 19), 1);
// 		vars->id_fork = vars->id_fork->next;
// 	}
// 	return (0);
// }

// void	create_list_id_fork()
// {
// 	int					counter;
// 	t_2link_circ_list	*lista;
// 	int					iter;

// 	iter = 3;
// 	counter = 0;
// 	lista = NULL;
// 	while (iter --)
// 	{
// 		create_2link_circlist(&lista, create_dictionary_int(NULL, &counter), NULL);
// 		printf("while %d\n", lista->next->content.value);
// 		// lista = lista->next;
// 		counter ++;
// 	}
// 	printf_content_2link_circ_list(lista);
// }

// int	create_routine_struct(int argc, char **argv, t_philo_routine *routine)
// {
// 	int				err;

// 	printf("hoal\n");
// 	(*routine).time_to_die = ft_atoi_chetao(argv[1], &err);
// 	if (err)
// 		return (0);
// 	(*routine).time_to_eat = ft_atoi_chetao(argv[2], &err);
// 	if (err)
// 		return (0);
// 	if (argc == 4)
// 		(*routine).time_to_sleep = ft_atoi_chetao(argv[3], &err);
// 		if (err)
// 			return (0);
// 	return (1);
// }
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
	if (argc == 5)
	{
		(*routine).time_to_sleep = ft_atoi_chetao(argv[3], &err);
	}
	if (err)
		return (1);
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
	n_philo = ft_atoi_chetao(argv[0], &err);
	if (err)
		return (NULL);
	if (create_routine_struct(argc, argv, &routine))
		return(NULL);
	counter = 0;
	while(n_philo)
	{
		if(create_2link_circlist(&lista, create_dictionary_int(counter), routine))
			return(perror("create_list_philo: "), NULL);
		n_philo --;
		counter ++;
	}
	return (lista);
}

int	main(int argc, char **argv)
{
	t_2link_circ_list	*list;

	argv ++;
	list = create_list_philo(argc, argv);
	
	if(!list)
		printf("NO HAY LISTA\n");

	printf_dlist_ind(list);

	// printf("ind ==  %d\n", list->id_fork.id);
	// printf("ind next ==  %d\n", list->next->id_fork.id);
	// printf("ind next next ==  %d\n", list->next->next->id_fork.id);
	// printf("\n\n");
	// printf("routine ==  %d %d %d\n", list->routine.time_to_die, list->routine.time_to_eat, list->routine.time_to_sleep);
	// printf("routine next ==  %d %d %d\n", list->next->routine.time_to_die, list->next->routine.time_to_eat, list->next->routine.time_to_sleep);
	// printf("routine next next ==  %d %d %d\n", list->next->next->routine.time_to_die, list->next->next->routine.time_to_eat, list->next->next->routine.time_to_sleep);
	if (list)
		clear_2link_circ_list(&list);
	//printf_dlist_ind(list);
	// t_philosophers	vars;
	// int				num_threads;
	// int				err;

	// create_list_id_fork();

	// if (verify_args(argc - 1, (argv + 1)))
	// 	return (1);
	// if (create_philo_struct(argc - 1, argv + 1, &vars))
	// 	return (write(2, "atoi fail\n", 11), 1);
	// num_threads = ft_atoi_chetao(argv[1], &err);
	// if (err)
	// 	return (write(2, "atoi fail\n", 11), 1);
	// if (create_threads(num_threads, &vars))
	// 	return (1);
	// return (0);
}

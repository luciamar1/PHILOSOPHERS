#include "philo.h"

void *f_hilo(void *args) 
{
	t_philosophers	*vars;

	vars = (t_philosophers *) args;
	printf("%d, %d, %d\n", vars->time_to_die, vars->time_to_eat, vars->time_to_sleep);
	printf("hola luci te quiero =)\n\n");
	return (NULL);
}

int	verify_args(int argc, char **argv)
{
	if (argc != 3 && argc != 4)
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

int	create_philo_struct(int argc, char **argv, t_philosophers	*vars)
{
	int				err;

	err = 0;
	(*vars).time_to_die = ft_atoi_chetao(argv[1], &err);
	if (err)
		return (1);
	(*vars).time_to_eat = ft_atoi_chetao(argv[2], &err);
	if (err)
		return (1);
	if (argc == 4)
		(*vars).time_to_sleep = ft_atoi_chetao(argv[3], &err);
	if (err)
		return (1);
	return (0);
}

int	create_threads(int threads, t_philosophers	*vars)
{
	int				creacion;
	pthread_t		threads_id[threads];
	int				counter;
	int				aux;
	int				espera;

	aux = threads;
	counter = 0;
	while (threads)
	{
		creacion = pthread_create(&(threads_id[counter]), NULL, f_hilo, vars);
		if (creacion)
			return (write(2, "pthread_create fail\n", 21), 1);
		counter ++;
		threads --;
	}
	counter = 0;
	while (aux --)
	{
		espera = pthread_join(threads_id[counter], NULL);
		if (espera)
			return (write(2, "wait pthread fail\n", 19), 1);
		counter ++;
	}
	return (0);
}

void	create_list_id_fork()
{
	int					counter;
	t_2link_circ_list	*lista;
	int					iter;

	iter = 3;
	counter = 0;
	lista = NULL;
	while (iter --)
	{
		create_2link_circlist(&lista, create_dictionary_int(NULL, &counter), NULL);
		printf("while %d\n", lista->next->content.value);
		// lista = lista->next;
		counter ++;
	}
	printf_content_2link_circ_list(lista);
}



int	main(int argc, char **argv)
{
	t_philosophers	vars;
	int				num_threads;
	int				err;

	create_list_id_fork();

	if (verify_args(argc - 1, (argv + 1)))
		return (1);
	if (create_philo_struct(argc - 1, argv + 1, &vars))
		return (write(2, "atoi fail\n", 11), 1);
	num_threads = ft_atoi_chetao(argv[1], &err);
	if (err)
		return (write(2, "atoi fail\n", 11), 1);
	if (create_threads(num_threads, &vars))
		return (1);
	return (0);
}

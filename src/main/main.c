#include "philosophers.h"

void *f_hilo(void *arg) 
{
	printf("%s\n", arg);
    return NULL;
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

int main(int argc, char **argv)
{
	pthread_t		thread_id;
	t_philosophers	vars;
	int				creacion;
	char			*mensaje = "hola luci te quiero =)\n";

	if (verify_args(argc - 1, (argv + 1)))
		return (1);
	if (create_philo_struct(argc - 1, argv + 1, &vars))
		return (write(2, "atoi fail\n", 11), 1);
	printf("%d, %d, %d\n", vars.time_to_die, vars.time_to_eat, vars.time_to_sleep);
	creacion = pthread_create(&thread_id, NULL, f_hilo, mensaje);
	if (creacion)
		printf("error\n");
	 int espera = pthread_join(thread_id, NULL);
    if (espera) {
        fprintf(stderr, "Error al esperar al hilo\n");
        return 1;
    }
	return(0);
}

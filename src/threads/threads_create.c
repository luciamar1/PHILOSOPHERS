#include "philo.h"

void	*f_hilo(void *args)
{
	t_2link_circ_list	*vars;
	vars = (t_2link_circ_list *) args;
	pthread_mutex_lock(&(vars->next->mutex.id));
	if (is_par(vars->id_fork.id))
		usleep(200);
	pthread_mutex_unlock(&(vars->next->mutex.id));
	
	eating(vars);
	thinking(vars);
	sleeping(vars);
	//printf("%d, %d, %d, %d\n", vars->routine.time_to_die, vars->routine.time_to_eat, vars->routine.time_to_sleep, vars->routine.number_of_times);
	pthread_mutex_lock(&(vars->mutex.print));
	printf("hola luci te quiero =)\n\n");
	pthread_mutex_unlock(&(vars->mutex.print));
	return (NULL);
}

int	create_threads(int n_threads, t_2link_circ_list *vars, pthread_t *threads)
{
	int					counter;
	int					aux;
	int					espera;

	counter = 0;
	aux = n_threads;
	while (aux)
	{
		if (pthread_create(&threads[counter], NULL, f_hilo, vars))
			return (perror("pthread_create fail\n"), 1);
		vars = vars->next;
		aux --;
		counter ++;
	}
	counter = 0;
	while (n_threads)
	{
		espera = pthread_join(threads[counter], NULL);
		if (espera)
			return (perror("wait pthread fail\n"), 1);
		n_threads --;
		counter ++;
	}
	return (0);
}

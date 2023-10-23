#include "philo.h"

void change_fork_value(t_2link_circ_list *vars, int state)
{
	// printf("ANTES philo %d is eating\n", vars->id_fork.fork);
	pthread_mutex_lock(&(vars->next->mutex.eat));
	vars->next->id_fork.fork = state;
	pthread_mutex_unlock(&(vars->next->mutex.eat));

	pthread_mutex_lock(&(vars->prev->mutex.eat));
	vars->prev->id_fork.fork = state;
	pthread_mutex_unlock(&(vars->prev->mutex.eat));
	// printf("DESPUES philo %d is eating\n", vars->id_fork.fork);

}

void	eating(t_2link_circ_list *vars)
{
	pthread_mutex_lock(&(vars->next->mutex.eat));
	change_fork_value(vars, 1);
	//u sleep
	change_fork_value(vars, 0);
	pthread_mutex_lock(&(vars->mutex.print));
	printf("philo %d is eating\n", vars->id_fork.id);
	pthread_mutex_unlock(&(vars->mutex.print));
	pthread_mutex_unlock(&(vars->mutex.eat));
}

void	sleeping(t_2link_circ_list *vars)
{
	pthread_mutex_lock(&(vars->mutex.print));
	printf("philo %d is sleeping\n", vars->id_fork.id);
	pthread_mutex_unlock(&(vars->mutex.print));
}

void	thinking(t_2link_circ_list *vars)
{
	pthread_mutex_lock(&(vars->mutex.print));
	printf("philo %d is thinking\n", vars->id_fork.id);
	pthread_mutex_unlock(&(vars->mutex.print));
}


void	*f_hilo(void *args)
{
	t_2link_circ_list	*vars;

	vars = (t_2link_circ_list *) args;
	pthread_mutex_lock(&(vars->next->mutex.id));
	if (is_par(vars->id_fork.id))
		usleep(100);
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

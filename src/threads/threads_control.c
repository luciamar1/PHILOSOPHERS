#include "philo.h"

void change_fork_value(pthread_mutex_t	*mutex_fork, int *fork, int state)
{
	pthread_mutex_lock(mutex_fork);
	*fork = state;
	pthread_mutex_unlock(mutex_fork);
}

int	try_to_take_fork(pthread_mutex_t	*mutex_fork, int *fork)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mutex_fork);
	if (*fork == 0)
	{
		ret = 1;
		*fork = 1;
	}
	pthread_mutex_unlock(mutex_fork);
	return (ret);
}

void	eating(t_2link_circ_list *vars)
{
	while (1)
	{
		if (try_to_take_fork(&(vars->next->mutex.fork), &(vars->next->id_fork.fork)))
		{
			if (try_to_take_fork(&(vars->mutex.fork), &(vars->id_fork.fork)))
			{
				//sleep
				pthread_mutex_lock(&(vars->mutex.print));
				printf("yuuuuuhuuuuuuuu estoy comiendooooo =)\n");
				pthread_mutex_unlock(&(vars->mutex.print));
				//change_2fork_values(vars, 0);
				change_fork_value(&(vars->next->mutex.fork), &(vars->next->id_fork.fork), 0);
				change_fork_value(&(vars->mutex.fork), &(vars->id_fork.fork), 0);
				break ;
			}
			else
				change_fork_value(&(vars->next->mutex.fork), &(vars->next->id_fork.fork), 0);
		}
		usleep(500);
	}
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



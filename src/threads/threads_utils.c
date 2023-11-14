#include "philo.h"

int	mutex_init(t_2link_circ_list *list)
{
	if (pthread_mutex_init(&(list->mutex.fork), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.print), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.id), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.eat), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.threads_ended), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.t_start_eating), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	if (pthread_mutex_init(&(list->mutex.t_born_philo), NULL))
		return (clear_philo(&list, NULL), perror(""), 1);
	return (0);
}

void	mutex_destroy(t_2link_circ_list *list)
{
	int	num;

	num = list->routine.n_philos;
	while (num)
	{
		pthread_mutex_destroy(&(list->mutex.fork));
		pthread_mutex_destroy(&(list->mutex.print));
		pthread_mutex_destroy(&(list->mutex.id));
		pthread_mutex_destroy(&(list->mutex.eat));
		pthread_mutex_destroy(&(list->mutex.threads_ended));
		pthread_mutex_destroy(&(list->mutex.t_start_eating));
		pthread_mutex_destroy(&(list->mutex.t_born_philo));
		list = list->next;
		num --;
	}
}
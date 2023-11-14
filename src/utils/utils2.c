#include "philo.h"

int	ft_usleep(long long useconds, t_2link_circ_list *philo)
{
	struct timeval	start_time;
	struct timeval	curr_time;
	long long		start_time_u;
	long long		curr_time_u;

	(void)philo;
	gettimeofday(&start_time, NULL);
	start_time_u = start_time.tv_sec * 1000000 + start_time.tv_usec;
	gettimeofday(&curr_time, NULL);
	curr_time_u = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	if (im_dead_(philo))
		return (1);
	while (curr_time_u - start_time_u < useconds)
	{
		usleep(500);
		gettimeofday(&curr_time, NULL);
		curr_time_u = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	}
	return (0);
}

void	ft_usleep_lucia(long long useconds, t_2link_circ_list *philo)
{
	int				counter;
	struct timeval	start_time;
	struct timeval	curr_time;
	long long		start_time_u;
	long long		curr_time_u;

	philo->im_dead = 0;
	gettimeofday(&start_time, NULL);
	counter = useconds;
	while (counter --)
	{
		usleep(1);
		gettimeofday(&curr_time, NULL);
	}
	gettimeofday(&curr_time, NULL);
	start_time_u = start_time.tv_sec * 1000000 + start_time.tv_usec;
	curr_time_u = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	printf("GUATAFAAAAAC == %lld\n", curr_time_u - start_time_u);
}
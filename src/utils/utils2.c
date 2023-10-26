#include "philo.h"

void	ft_miguel_usleep(long long useconds)
{
	struct timeval	start_time;
	struct timeval	curr_time;
	long long		start_time_u;
	long long		curr_time_u;

	gettimeofday(&start_time, NULL);
	start_time_u = start_time.tv_sec * 1000000 + start_time.tv_usec;
	gettimeofday(&curr_time, NULL);
	curr_time_u = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	while (curr_time_u - start_time_u < useconds)
	{
		usleep(500);
		// if (philo && (end_value(philo) || check_philo_dead(philo)))
		// 	break ;
		gettimeofday(&curr_time, NULL);
		curr_time_u = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	}
}

void	ft_usleep(long long useconds)
{
	int counter;
	struct timeval	start_time;
	struct timeval	curr_time;


	gettimeofday(&start_time, NULL);
	counter = useconds;
	while(counter --)
	{
		gettimeofday(&curr_time, NULL);
		usleep(1);
		gettimeofday(&curr_time, NULL);
		
	}
}
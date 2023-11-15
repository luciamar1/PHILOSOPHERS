#include "philo.h"

int	ft_usleep_miguel(long long useconds, t_2link_circ_list *philo)
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

uint64_t	get_timeval_ms(struct timeval *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}

int	ft_usleep(long long useconds, t_2link_circ_list *philo)
{
	struct timeval	start;
	uint64_t		time;
	uint64_t		end_ms;

	(void) philo;
	gettimeofday(&start, NULL);
	time = get_timeval_ms(&start);
	end_ms = time + useconds;
	while (time < end_ms)
	{
		gettimeofday(&start, NULL);
		time = get_timeval_ms(&start);
		usleep(100);
	}
	// int				counter;
	// struct timeval	start_time;
	// struct timeval	curr_time;
	// long long		start_time_u;
	// long long		curr_time_u;

	// philo->im_dead = 0;
	// gettimeofday(&start_time, NULL);
	// counter = useconds;
	// while (counter --)
	// {
	// 	usleep(1);
	// 	gettimeofday(&curr_time, NULL);
	// }
	// gettimeofday(&curr_time, NULL);
	// start_time_u = start_time.tv_sec * 1000000 + start_time.tv_usec;
	// curr_time_u = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	// printf("GUATAFAAAAAC == %lld\n", curr_time_u - start_time_u);
	return (0);
}


void	ft_cabezas_usleep(int no_philos, uint64_t millisec)
{
	struct timeval	start;
	uint64_t		time;
	uint64_t		end_ms;

	gettimeofday(&start, NULL);
	time = get_timeval_ms(&start);
	end_ms = time + millisec;
	while (time < end_ms)
	{
		gettimeofday(&start, NULL);
		time = get_timeval_ms(&start);
		usleep(no_philos);
	}
}
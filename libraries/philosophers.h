#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philosophers
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}   t_philosophers;

int	ft_arr_isdigit(char *arr);
int	ft_atoi_chetao(const char *str, int *error);

#endif

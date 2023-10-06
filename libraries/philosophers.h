#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_ldictionary
{
    pthread_t key;
    int value;
    struct s_ldictionary *next;
}   t_ldictionary;

typedef struct s_philosophers
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    t_ldictionary   *id_fork;
}   t_philosophers;

// utils
int             ft_arr_isdigit(char *arr);
int	            ft_atoi_chetao(const char *str, int *error);

// utils_list
t_ldictionary	*l_dictionary_new(pthread_t key, int value);
void            l_dictionary_add_back(t_ldictionary **lst, t_ldictionary *new);

#endif

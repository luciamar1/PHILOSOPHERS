#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_dictionary
{
	int	id;
	int	fork;
}	t_dictionary;

typedef struct s_philo_routine
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}	t_philo_routine;

typedef struct s_2link_circ_list
{
	t_dictionary				id_fork;
	t_philo_routine				routine;
	struct s_2link_circ_list	*next;
	struct s_2link_circ_list	*prev;
}	t_2link_circ_list;



//    utils
int	ft_arr_isdigit(char *arr);
int	ft_atoi_chetao(const char *str, int *error);
t_dictionary	create_dictionary_int(int id);

//     utils  2linked circle list
int	create_2link_circlist(t_2link_circ_list **head, t_dictionary id_fork, t_philo_routine routine);
void	printf_fork_2link_circ_list(t_2link_circ_list *list);
int		len_dlist(t_2link_circ_list *stack);
void	printf_dlist_ind(t_2link_circ_list *list);
int		clear_2link_circ_list(t_2link_circ_list **list);

#endif

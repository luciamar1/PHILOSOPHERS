#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

// COLORS
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PINK	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define FN		"\033[0m"
/// SOLO UN MUTEX PARA PRINT
typedef struct s_mutex
{
	pthread_mutex_t	fork;
	pthread_mutex_t	threads_ended;
	pthread_mutex_t	print;
	pthread_mutex_t	id;
	pthread_mutex_t	im_arriving;
	pthread_mutex_t	t_start_eating;
	pthread_mutex_t t_born_philo;
}	t_mutex;

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
	int					number_of_times;
	int					n_philos;
}	t_philo_routine;

//[3000ms] 2 is thinking
//born filo unico

typedef struct s_2link_circ_list
{
	pthread_mutex_t				*mutex_im_dead;
	pthread_mutex_t				*mutex_all_sit;
	int							*dead;
	int							*all_sit;
	int							arriving_philos;
	int							threads_ended;
	int							im_dead;
	t_dictionary				id_fork;
	t_philo_routine				routine;
	t_mutex						mutex;
	struct timeval				start_eating;
	struct timeval				born_philo;
	struct s_2link_circ_list	*next;
	struct s_2link_circ_list	*prev;
}	t_2link_circ_list;



//    utils
int	ft_arr_isdigit(char *arr);
int	ft_atoi_chetao(const char *str, int *error);
t_dictionary	create_dict_int(int id);
int	is_impar(int num);
void	clear_philo(t_2link_circ_list **vars, pthread_t **id_threads);
void	ft_miguel_usleep(long long useconds);
int	ft_usleep(long long useconds, t_2link_circ_list *philo);



//     utils  2linked circle list
int	create_2link_circlist(t_2link_circ_list **head, t_dictionary id_fork, \
	t_philo_routine routine, int *dead, int *all_sit);
void	printf_fork_2link_circ_list(t_2link_circ_list *list);
int		len_dlist(t_2link_circ_list *stack);
void	printf_dlist_ind(t_2link_circ_list *list);
int		clear_2link_circ_list(t_2link_circ_list **list);

//      threads_create
void	*f_hilo(void *args);
int		create_threads(int n_threads, t_2link_circ_list *vars, pthread_t *threads);

//      threads_utils
int		mutex_init(t_2link_circ_list *list);
void	mutex_destroy(t_2link_circ_list *list);
void	calculate_thread_death(t_2link_circ_list *vars);
int	im_dead_(t_2link_circ_list *vars);
//void	wait_to_sit(t_2link_circ_list *vars);

//		threads_control
int	eating(t_2link_circ_list *vars);
int	sleeping(t_2link_circ_list *vars);
void	thinking(t_2link_circ_list *vars);


#endif

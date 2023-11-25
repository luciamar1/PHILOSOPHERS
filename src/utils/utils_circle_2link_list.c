/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_circle_2link_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:47:35 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/11/25 04:19:18 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_2link_circlist(t_2link_circ_list **head, t_dictionary id_fork, \
	t_philo_routine routine, int *dead, int *all_sit)
{
	t_2link_circ_list	*new;

	new = malloc(sizeof(t_2link_circ_list));

	if (!new || mutex_init(new))
	{
		if (*head)
			clear_2link_circ_list(head);
		return (1);
	}
	if (!*head)
	{
		new->mutex_im_dead = malloc(sizeof(pthread_mutex_t));
		if (!new->mutex_im_dead)
			return (clear_philo(&new, NULL), perror(""), 1);
		new->mutex_all_sit = malloc(sizeof(pthread_mutex_t));
		if (!new->mutex_all_sit)
			return (clear_philo(&new, NULL), perror(""), 1);
		if (pthread_mutex_init((new->mutex_all_sit), NULL))
			return (clear_philo(&new, NULL), perror(""), 1);
		printf("aaaaaaa %p\n", new->mutex_all_sit);
		if (pthread_mutex_init((new->mutex_im_dead), NULL))
			return (clear_philo(&new, NULL), perror(""), 1);
	}
	else
	{
		new->mutex_im_dead = (*head)->mutex_im_dead;
		new->mutex_all_sit = (*head)->mutex_all_sit;
	}
	new->dead = dead;
	new->all_sit = all_sit;
	//new->arriving_philos = 0;
	new->id_fork = id_fork;
	new->routine = routine;
	new->threads_ended = 0;
	// printf("guatafac\n");
	// printf("mutex ==  %p\n", new->mutex_im_dead);
	if (!*head)
		new->next = (new->prev = new, new);
	else
	{
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev = new;
		new->prev->next = new;
	}
	*head = new->next ;
	return (0);
}

void	printf_fork_2link_circ_list(t_2link_circ_list *list)
{
	t_2link_circ_list	*head;

	head = list;
	printf("\n\n\n");
	printf("id_fork list == %d\n", list->id_fork.fork);
	list = list->next;
	while (list != head)
	{
		if (list->id_fork.fork)
			printf("id_fork list == %d\n", list->id_fork.fork);
		list = list->next;
	}
}

int	len_dlist(t_2link_circ_list *stack)
{
	int					len;
	t_2link_circ_list	*init;

	if (!stack)
		return (0);
	len = 1;
	init = stack;
	stack = stack->next;
	while (stack != init)
	{
		len ++;
		stack = stack->next;
	}
	return (len);
}

void	printf_dlist_ind(t_2link_circ_list *list)
{
	t_2link_circ_list	*start;

	if (!list)
		return ;
	start = list;
	printf("ind list == %d\n", (int) list->id_fork.id);
	if (list->next)
		list = list->next;
	while (list != start)
	{
		printf("ind list  ==  %d\n", (int) list->id_fork.id);
		if (list->next)
			list = list->next;
	}
	printf("\n\n");
}

int	clear_2link_circ_list(t_2link_circ_list **list)
{
	t_2link_circ_list	*aux;
	t_2link_circ_list	*next_aux;

	if (!*list)
		return (1);
	aux = *list;
	next_aux = (*list)->next;
	while (next_aux != *list)
	{
		if (aux)
			free(aux);
		aux = next_aux;
		next_aux = aux->next;
	}
	if (aux)
		free(aux);
	*list = NULL;
	return (0);
}

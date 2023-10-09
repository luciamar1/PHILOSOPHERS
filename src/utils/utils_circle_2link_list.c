/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_circle_2link_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:47:35 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/10/09 19:55:54 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	create_2link_circlist(t_2link_circ_list **head, t_dictionary *content, pthread_t id)
{
	t_2link_circ_list	*new;

	new = malloc(sizeof(t_2link_circ_list));
	if (!new)
	{
		clear_2link_circ_list(head);
		return (1);
	}
	if (content)
		new->content = content;
	if (id)
		new->id = id;
	if (!*head)
	{
		new->prev = new;
		printf("new content 1== %d\n", new->content);
		new->next = new;
	}
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

void	printf_content_2link_circ_list(t_2link_circ_list *list)
{
	t_2link_circ_list	*head;

	head = list;
	printf("\n\n\n");
	printf("content list == %d\n", list->content);
	list = list->next;
	while (list != head)
	{
		// printf("que?\n");
		if(list->content)
			printf("content list == %d\n", list->content);
		// printf("aaaaaaa\n");
		// printf("aaaaa%d\n", list->content != head->content);
		// printf("next == %p\n", list->next);
		list = list->next;
	}
}

int	len_dlist(t_2link_circ_list *stack)
{
	int		len;
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

	start = list;
	printf("ind list == %d\n", (int) list->id);
	list = list->next;
	while (list->content != start->content)
	{
		printf("ind list  ==  %d\n", (int) list->id);
		list = list->next;
	}
	printf("caracol\n");
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
		free(aux);
		aux = next_aux;
		next_aux = aux->next;
	}
	free(aux);
	*list = NULL;
	return (0);
}

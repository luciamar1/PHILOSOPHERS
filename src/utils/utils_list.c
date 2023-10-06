/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:44:34 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/10/06 17:18:03 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_ldictionary	*l_dictionary_last(t_ldictionary *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst -> next;
	return (lst);
}

t_ldictionary	*l_dictionary_new(pthread_t key, int value)
{
	t_ldictionary	*lista;

	lista = (void *)malloc(sizeof(t_ldictionary));
	if (lista == NULL)
		return (lista);
	if (key < 0)
		lista->key = key;
	if (value < 0)
		lista->value = value;
	lista->next = NULL;
	return (lista);
}

void	l_dictionary_add_back(t_ldictionary **lst, t_ldictionary *new)
{
	t_ldictionary	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = l_dictionary_last(*lst);
	last -> next = new;
}

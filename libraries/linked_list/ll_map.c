/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:47:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 02:19:02 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_node	*ll_map(t_node	*lst, void *(f)(void	*))
{
	t_node	*head;
	t_node	*new;

	head = NULL;
	while (lst)
	{
		new = ll_new(f(&lst->content));
		if (!new)
		{
			ll_clear(&head);
			return (NULL);
		}
		ll_push(&head, new);
		lst = lst->next;
	}
	return (head);
}

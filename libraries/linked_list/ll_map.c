/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:47:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 05:10:01 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * returns a linked list in which the nodes are the inital lists nodes with the function f applied to them.
*/
t_node	*ll_map(t_node	*head, void *(f)(void	*))
{
	t_node	*head;
	t_node	*new;

	head = NULL;
	while (head)
	{
		new = ll_new(f(&head->content));
		if (!new)
		{
			ll_clear(&head);
			return (NULL);
		}
		ll_push(&head, new);
		head = head->next;
	}
	return (head);
}

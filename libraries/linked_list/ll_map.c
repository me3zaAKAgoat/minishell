/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:47:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/30 17:02:22 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * Returns a linked list where each node contains the content
 * of the initial list's nodes, with the function f applied to them.
*/
t_node	*ll_map(t_node	*head, void *(f)(void	*))
{
	t_node	*new_list;
	t_node	*tmp;

	new_list = NULL;
	while (head)
	{
		tmp = ll_new(f(&head->content));
		if (!tmp)
		{
			ll_clear(&head);
			return (NULL);
		}
		ll_push(&new_list, tmp);
		head = head->next;
	}
	return (new_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:41:42 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 05:07:54 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * Clear all nodes of a linked list from the heap.
*/
void	ll_clear(t_node	**head)
{
	t_node	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		ll_del_one(*head, NULL);
		(*head) = tmp;
	}
	*head = NULL;
}

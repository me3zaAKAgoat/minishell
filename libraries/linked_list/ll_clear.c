/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:41:42 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/25 18:32:26 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * Clear all nodes of a linked list from the heap.
*/
void	ll_clear(t_node	**head, void (free_content)(void *))
{
	t_node	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		ll_del_one(*head, free_content);
		(*head) = tmp;
	}
	*head = NULL;
}

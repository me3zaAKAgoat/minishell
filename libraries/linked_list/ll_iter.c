/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_iter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:44:49 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 05:07:33 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * iterate over the linked list and apply a function to the content of each node.
 * 
 * @param f function to apply to content of nodes.
*/
void	ll_iter(t_node	*head, int (f)(void	*))
{
	while (head)
	{
		f(&head->content);
		head = head->next;
	}
}

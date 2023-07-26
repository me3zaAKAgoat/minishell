/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_del_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 22:44:28 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/26 10:24:40 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * Clear a node from the heap.
 * 
 * @param node node to clear.
 * @param free_content optional function to clear
 * the content of node (if null does nothing).
*/
void	ll_del_one(t_node *node, void (free_content)(void *))
{
	if (free_content)
		free_content(node->content);
	free(node);
}

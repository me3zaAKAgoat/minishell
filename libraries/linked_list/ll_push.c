/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:08:16 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 05:12:55 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * @param head_p pointer to head of the list to push the node to.
 * @param new the node to add to the end of the list.
*/
void	ll_push(t_node **head_p, t_node *new)
{
	if (*head_p)
	{
		ll_last(*head_p)->next = new;
		new->next = NULL;
	}
	else
		*head_p = new;
}

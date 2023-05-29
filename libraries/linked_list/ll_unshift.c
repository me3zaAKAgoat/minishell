/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_unshift.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:08:31 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 05:14:25 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * adds a node to the start of the linked list.
*/
void	ll_unshift(t_node **head_p, t_node *new)
{
	new->next = *head_p;
	*head_p = new;
}

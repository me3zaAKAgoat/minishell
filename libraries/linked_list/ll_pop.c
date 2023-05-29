/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:30:36 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 05:11:53 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * removes the last node of list.
*/
void	ll_pop(t_node *head)
{
	ll_del_one(ll_last(head), NULL);
	ll_atindex(head, ll_size(head) - 1)->next = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:30:36 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/30 16:53:45 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/**
 * removes the last node of list.
*/
t_node	*ll_pop(t_node **head_p, int index)
{
	t_node	*tmp;

	if (index == 0)
		return (ll_shift(head_p));
	else if (index == -1)
	{
		tmp = ll_last(*head_p);
		ll_atindex(*head_p, ll_size(*head_p) - 1)->next = NULL;
	}
	else
	{
		tmp = ll_atindex(*head_p, index);
		ll_atindex(*head_p, index - 1)->next = tmp->next;
	}
	return (tmp);
}

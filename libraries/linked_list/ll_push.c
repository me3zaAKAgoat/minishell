/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:08:16 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 01:54:27 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

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

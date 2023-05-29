/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_shift.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:30:36 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/29 02:38:27 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	ll_shift(t_node **head_p)
{
	t_node	*old_head;

	old_head = *head_p;
	*head_p = (*head_p)->next;
	ll_del_one(old_head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:30:36 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/28 23:00:15 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	ll_pop(t_node *head)
{
	ll_del_one(ll_last(head));
	ll_atindex(head, ll_size(head) - 1)->next = NULL;
}

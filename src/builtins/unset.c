/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:30:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/19 14:39:12 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **args)
{
	t_node	*iterator;
	t_dict	*kvp;

	iterator = g_meta.env;
	while (iterator)
	{
		kvp = iterator->content;
		if (!ft_strcmp(args[1], kvp->key))
		{
			ll_del_one(ll_pop(&g_meta.env,
					ll_get_index(g_meta.env, iterator)), (void*)clear_kvp);
			break ;
		}
		iterator = iterator->next;
	}
}

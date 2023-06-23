/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:30:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 15:20:54 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **args)
{
	t_node	*iterator;
	t_dict	*kvp;

	if (args[1])
	{
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
		g_meta.status = 0;
	}
	else
		g_meta.status = BUILTIN_FAIL;
}

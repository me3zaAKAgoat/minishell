/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:30:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/01 02:59:34 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_meta *meta, char *key)
{
	t_node	*iterator;
	t_dict	*kvp;

	iterator = meta->env;
	while (iterator)
	{
		kvp = iterator->content;
		if (!ft_strncmp(key, kvp->key, ft_strlen(kvp->key)))
		{
			ll_del_one(ll_pop(&meta->env,
					ll_get_index(meta->env, iterator)), (void*)clear_kvp);
			break ;
		}
		iterator = iterator->next;
	}
}

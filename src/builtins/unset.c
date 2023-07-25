/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:30:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/27 20:31:14 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_identifier(char *str)
{
	werror("Minishell: export: `");
	werror(str);
	werror("': not a valid identifier\n");
	return (1);
}

void	ft_unset(char **args)
{
	t_node	*iterator;
	t_dict	*kvp;
	int		i;

	g_meta.status = 0;
	i = 1;
	while (args[i])
	{
		iterator = g_meta.env;
		while (iterator)
		{
			kvp = iterator->content;
			if (key_is_valid(args[i]) != 1 && invalid_identifier(args[i]))
				break ;
			else if (!ft_strcmp(args[i], kvp->key))
			{
				ll_del_one(ll_pop(&g_meta.env,
						ll_get_index(g_meta.env, iterator)), (void*)clear_kvp);
				break ;
			}
			iterator = iterator->next;
		}
		i++;
	}
}

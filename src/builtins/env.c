/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:38:08 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/19 14:38:57 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **args)
{
	t_node	*iterator;
	t_dict	*kvp;

	(void)args;
	iterator = g_meta.env;
	while (iterator)
	{
		kvp = iterator->content;
		if (kvp->value)
		{
			write(1, kvp->key, ft_strlen(kvp->key));
			write(1, "=", ft_strlen("="));
			write(1, kvp->value, ft_strlen(kvp->value));
			write(1, "\n", ft_strlen("\n"));
		}
		iterator = iterator->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:38:56 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/03 04:27:21 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_env(char **env)
{
	t_node	*head;
	char	**arr;
	t_dict	*tmp;

	if (!env)
		return (NULL);
	head = NULL;
	while (*env)
	{
		arr = ft_split(*env, '=');
		tmp = new_kvp(arr[0], arr[1]);
		if (tmp)
			ll_push(&head, ll_new(tmp));
		split_clear(arr);
		env++;
	}
	return (head);
}

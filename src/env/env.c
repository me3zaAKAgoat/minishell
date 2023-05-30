/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:38:56 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/30 10:29:55 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*init_env(char **env)
{
	t_node	*head;
	char	**arr;

	head = NULL;
	while (*env)
	{
		arr = ft_split(*env, '=');
		ll_push(&head, ll_new(new_kvp(arr[0], arr[1])));
		free(arr);
		env++;
	}
	return (head);
}
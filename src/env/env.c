/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:38:56 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/03 09:44:13 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(t_node *env, char *key)
{
	t_dict	*kvp;

	while (env)
	{
		kvp = env->content;
		if (!ft_strncmp(key, kvp->key, ft_strlen(kvp->key)))
			return (kvp->value);
		env = env->next;
	}
	return (NULL);
}

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

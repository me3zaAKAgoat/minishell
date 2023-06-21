/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:55:15 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/20 02:54:19 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * clears a key value pair dict variable from the heap
*/
void	clear_kvp(t_dict *kvp)
{
	free(kvp->key);
	free(kvp->value);
	free(kvp);
}

/**
 * get a key from dictionary 
*/
t_dict	*get_kvp(t_node *kvp_list, char *key)
{
	while (kvp_list)
	{
		if (!ft_strcmp(((t_dict *)kvp_list->content)->key, key))
			return (((t_dict *)kvp_list->content));
		kvp_list = kvp_list->next;
	}
	return (NULL);
}

/**
 * sets a key value pair of dictionary type
*/
t_dict	*new_kvp(char *key, char *val)
{
	t_dict	*kvp;

	if (!key)
		return (NULL);
	kvp = malloc(sizeof(t_dict));
	if (!kvp)
		return (NULL);
	kvp->key = ft_strdup(key);
	kvp->value = ft_strdup(val);
	return (kvp);
}

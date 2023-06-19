/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:55:15 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/01 02:59:44 by echoukri         ###   ########.fr       */
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
t_dict *get_kvp(t_node *kvp_list, char *key)
{
	t_dict	*kvp;
	t_node	*iterator;

	iterator = kvp_list;
	while (iterator)
	{
		kvp = iterator->content;
		if (!ft_strcmp(kvp->key, key))
			return (kvp);
		iterator = iterator->next;
	}
	return (NULL);
}


/**
 * sets a key value pair of dictionary type
*/
t_dict	*new_kvp(char *key, char *val)
{
	t_dict	*kvp;
	char	*h_key;
	char	*h_val;

	if (!key || !val)
		return (NULL);
	kvp = malloc(sizeof(t_dict));
	h_key = malloc(ft_strlen(key) + 1);
	h_val = malloc(ft_strlen(val) + 1);
	if (!kvp || !h_key || !h_val)
		return (NULL);
	ft_strlcpy(h_key, key, ft_strlen(key) + 1);
	ft_strlcpy(h_val, val, ft_strlen(val) + 1);
	kvp->key = h_key;
	kvp->value = h_val;
	return (kvp);
}

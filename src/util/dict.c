/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:55:15 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/31 14:11:15 by echoukri         ###   ########.fr       */
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
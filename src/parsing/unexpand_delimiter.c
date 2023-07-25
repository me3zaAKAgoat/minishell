/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpand_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:40:56 by ekenane           #+#    #+#             */
/*   Updated: 2023/07/21 14:42:47 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unexpand_heredoc_delimiter(char *delim)
{
	t_node	*iterator;
	t_dict	*kvp;

	iterator = g_meta.env;
	while (iterator)
	{
		kvp = iterator->content;
		if (!ft_strcmp(kvp->value, delim))
			return (ft_strjoin("$", kvp->key));
		iterator = iterator->next;
	}
	return (NULL);
}

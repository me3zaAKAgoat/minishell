/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:57:47 by ekenane           #+#    #+#             */
/*   Updated: 2023/07/21 14:59:01 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_to_result(char *str, char *substring)
{
	char	*new_str;

	if (!str && !substring)
		return (NULL);
	new_str = ft_strjoin(str, substring);
	free(str);
	free(substring);
	return (new_str);
}

int	count_key_length(char *key, int i)
{
	while (key[i] && !ft_isspace(key[i])
		&& key[i] != '"' && key[i] != '$'
		&& (ft_isalpha(key[i]) || key[i] == '_' || ft_isdigit(key[i])))
		i++;
	return (i);
}

void	is_delimiter_inside_quotes(t_node *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == HEREDOC)
		{
			tokens = tokens->next;
			while (tokens)
			{
				token = tokens->content;
				if (token->type != SPACEE)
					break ;
				tokens = tokens->next;
			}
			if (token->type == DQUOTE || token->type == SQUOTE)
				g_meta.flags.expansion_heredoc = 0;
		}
		tokens = tokens->next;
	}
}

char	*remove_last_quote(char *str)
{
	char	*tmp;

	tmp = str;
	str = ft_strtrim(tmp, "\"");
	free(tmp);
	return (str);
}

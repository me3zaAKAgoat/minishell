/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:57:47 by ekenane           #+#    #+#             */
/*   Updated: 2023/08/04 10:48:06 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*skip_wspaces(t_node *tokens)
{
	tokens = tokens->next;
	while (tokens && ((t_token *)tokens->content)->type == WSPACE)
		tokens = tokens->next;
	return (tokens);
}

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
	while (tokens)
	{
		if (((t_token *)tokens->content)->type == HEREDOC)
		{
			tokens = tokens->next;
			while (tokens && ((t_token *)tokens->content)->type == WSPACE)
				tokens = tokens->next;
			while (tokens && ((t_token *)tokens->content)->type != WSPACE)
			{
				if (((t_token *)tokens->content)->type == DQUOTE
					|| ((t_token *)tokens->content)->type == SQUOTE)
				{
					g_meta.flags.expansion_heredoc = 0;
					break ;
				}
				else
					g_meta.flags.expansion_heredoc = 1;
				tokens = tokens->next;
			}
		}
		else
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

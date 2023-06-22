/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:13:19 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/22 03:32:02 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_to_result(char *str, char *substring)
{
	char	*new_str;

	new_str = ft_strjoin(str, substring);
	free(str);
	free(substring);
	return (new_str);
}

char	*expanded_string(char	*initial_str)
{
	char	*str;
	char	*key;
	int		i;
	int		j;

	str = NULL;
	key = NULL;
	j = 0;
	i = 0;
	while (initial_str[i])
	{
		if (initial_str[i] == '$' && initial_str[i + 1])
		{
			str = append_to_result(str, ft_substr(initial_str, j, i - j));
			if (initial_str[i + 1] == '?')
			{
				str = append_to_result(str, ft_itoa(g_meta.status));
				i += 2;
			}
			else
			{				
				j = i + 1;
				while (initial_str[i] && !ft_isspace(initial_str[i]))
					i++;
				key = ft_substr(initial_str, j, i - j);
				str = append_to_result(str,
						ft_strdup(get_kvp(g_meta.env, key)->value));
				free(key);
			}
			j = i;
		}
		else
			i++;
	}
	return (append_to_result(str, ft_substr(initial_str, j, i - j)));
}

void	expand_envs(t_node *tokens)
{
	t_token	*token;
	char	*tmp;

	while (tokens)
	{
		token = ((t_token *)tokens->content);
		if (token->type == STRING || token->type == DQUOTE)
		{
			tmp = token->value;
			token->value = expanded_string(tmp);
			free(tmp);
		}
		tokens = tokens->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:13:19 by echoukri          #+#    #+#             */
/*   Updated: 2023/08/05 22:36:21 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_special_vars(char *initial_str, int *i, char *str)
{
	if (initial_str[(*i)] == '?')
		str = append_to_result(str, ft_itoa(g_meta.status));
	else if (initial_str[(*i)] == '$')
		str = append_to_result(str, ft_strdup("$$"));
	(*i) += 1;
	return (str);
}

char	*expand_vars(int *j, int *i, char *initial_str, char *str)
{
	char	*key;
	char	*value;

	(*j) = (*i);
	(*i) = count_key_length(initial_str, (*i));
	key = ft_substr(initial_str, (*j), (*i) - (*j));
	if (key_is_valid(key) != 1)
	{
		str = append_to_result(str, ft_strdup("$"));
		str = append_to_result(str, ft_strdup(key));
	}
	else if (!get_kvp(g_meta.env, key))
		return (free(key), NULL);
	else if (get_kvp(g_meta.env, key))
	{
		value = get_kvp(g_meta.env, key)->value;
		if (!ft_strchr(initial_str, '\"'))
			str = rm_expanded_extra_wspace(str, value);
		else
			str = append_to_result(str, ft_strdup(value));
	}
	free(key);
	return (str);
}

char	*expand_process(int *i, int *j, char *initial_str, char *str)
{
	char	*tmp;

	if (initial_str[(*i)] == '?' || initial_str[(*i)] == '$')
		str = expand_special_vars(initial_str, i, str);
	else
	{
		tmp = expand_vars(j, i, initial_str, str);
		if (!tmp)
			return (NULL);
		else
			str = tmp;
	}
	(*j) = (*i);
	return (str);
}

char	*expanded_string(char	*initial_str)
{
	char	*str;
	char	*tmp;
	int		i;
	int		j;

	str = NULL;
	j = 0;
	i = 0;
	while (initial_str[i])
	{
		if (initial_str[i] == '$' && initial_str[i + 1]
			&& initial_str[i + 1] != '"' && !ft_isspace(initial_str[i + 1]))
		{
			i += 1;
			tmp = expand_process(&i, &j, initial_str, str);
			if (!tmp)
				continue ;
			else
				str = tmp;
		}
		else
			str = append(initial_str, str, &i, &j);
	}
	str = remove_last_quote(str);
	return (str);
}

void	expand_envs(t_node *tokens)
{
	t_token	*token;
	char	*tmp;

	is_delimiter_inside_quotes(tokens);
	while (tokens)
	{
		token = ((t_token *)tokens->content);
		if (token->type == HEREDOC)
			tokens = skip_wspaces(tokens)->next;
		else if (token->type == STRING || token->type == DQUOTE)
		{
			tmp = token->value;
			token->value = expanded_string(tmp);
			if (token->type == STRING)
				split_expand_value(tokens);
			else if (token->type == DQUOTE)
				token->type = STRING;
			free(tmp);
			tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
}

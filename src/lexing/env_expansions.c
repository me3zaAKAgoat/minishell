/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:13:19 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/28 06:31:03 by echoukri         ###   ########.fr       */
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

char	*expand_special_vars(char *initial_str, int *i, char *str)
{
	if (initial_str[(*i)] == '?')
		str = append_to_result(str, ft_strdup(ft_itoa(g_meta.status)));
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
		str = append_to_result(str, ft_strdup(key));
	else if (!get_kvp(g_meta.env, key))
		return (NULL);
	else if (get_kvp(g_meta.env, key))
	{
		value = get_kvp(g_meta.env, key)->value;
		str = append_to_result(str, ft_strdup(value));
	}
	free(key);
	return (str);
}

char	*append_dollar(int *j, int *i, char *str)
{
	str = append_to_result(str, ft_strdup("$"));
	(*i) += 1;
	(*j) = (*i);
	return (str);
}

char	*append_normal_text(int *j, int *i, char *initial_str, char *str)
{
	(*j) = (*i);
	if (i == 0 && initial_str[(*i)] == '"')
		(*j) += 1;
	while (initial_str[(*i)] && initial_str[(*i)] != '$')
		(*i)++;
	str = append_to_result(str, ft_substr(initial_str, (*j), (*i) - (*j)));
	return (str);
}

char	*remove_last_quote(char *str)
{
	char	*tmp;

	tmp = str;
	str = ft_strtrim(tmp, "\"");
	free(tmp);
	return (str);
}

char	*append(char *initial_str, char *str, int *i, int *j)
{
	if (initial_str[(*i)] == '$')
		str = append_dollar(j, i, str);
	else
		str = append_normal_text(j, i, initial_str, str);
	return (str);
}

char	*expanded_string(char	*initial_str)
{
	char	*str;
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
			if (initial_str[i] == '?' || initial_str[i] == '$')
				str = expand_special_vars(initial_str, &i, str);
			else
			{
				if (!expand_vars(&j, &i, initial_str, str))
					continue ;
				else
					str = expand_vars(&j, &i, initial_str, str);
			}
			j = i;
		}
		else
			append(initial_str, str, &i, &j);
	}
	str = remove_last_quote(str);
	return (str);
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

void	expand_envs(t_node *tokens)
{
	t_token	*token;
	char	*tmp;
	char	**arr_strs;

	is_delimiter_inside_quotes(tokens);
	while (tokens)
	{
		token = ((t_token *)tokens->content);
		if (token->type == STRING || token->type == DQUOTE)
		{
			tmp = token->value;
			if (ft_strchr(tmp, '$'))
			{
				token->value = expanded_string(tmp);
				arr_strs = ft_split(token->value, ' ');
				free(token->value);
				token->value = join_arr(arr_strs, " ");
				token->type = STRING;
				free(tmp);
			}
		}
		tokens = tokens->next;
	}
}

// char	*append_to_result(char *str, char *substring)
// {
// 	char	*new_str;

// 	new_str = ft_strjoin(str, substring);
// 	free(str);
// 	free(substring);
// 	return (new_str);
// }

// int	expand_string_helper(char	*s1, char *s2, int i, int j)
// {
// 	char	*key;

// 	key = NULL;
// 	s2 = append_to_result(s2, ft_substr(s1, j, i - j));
// 	if (s1[i + 1] == '?')
// 	{
// 		s2 = append_to_result(s2, ft_itoa(g_meta.status));
// 		i += 2;
// 	}
// 	else
// 	{
// 		j = i + 1;
// 		while (s1[i] && !ft_isspace(s1[i]))
// 			i++;
// 		key = ft_substr(s1, j, i - j);
// 		if (get_kvp(g_meta.env, key))
// 			s2 = append_to_result(s2,
// 					ft_strdup(get_kvp(g_meta.env, key)->value));
// 		free(key);
// 	}
// 	return (i);
// }

// char	*expand_string(char	*initial_str)
// {
// 	char	*expanded_string;
// 	int		i;
// 	int		j;

// 	expanded_string = NULL;
// 	j = 0;
// 	i = 0;
// 	while (initial_str[i])
// 	{
// 		if (initial_str[i] == '$' && initial_str[i + 1])
// 		{
// 			i = expand_string_helper(initial_str, expanded_string, i, j);
// 			j = i;
// 		}
// 		else
// 			i++;
// 	}
// 	return (append_to_result(expanded_string, ft_substr(initial_str, j, i - j)));
// }

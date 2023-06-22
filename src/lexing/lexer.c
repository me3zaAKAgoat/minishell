/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:37:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/22 03:40:40 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_next_token(char *cmd_line)
{
	if (!ft_strncmp("<<", cmd_line, 2))
		return (new_token(ft_strdup("<<"), HEREDOC));
	else if (!ft_strncmp(">>", cmd_line, 2))
		return (new_token(ft_strdup(">>"), APPEND));
	else if (!ft_strncmp("<", cmd_line, 1))
		return (new_token(ft_strdup("<"), IN));
	else if (!ft_strncmp(">", cmd_line, 1))
		return (new_token(ft_strdup(">"), OUT));
	else if (!ft_strncmp("|", cmd_line, 1))
		return (new_token(ft_strdup("|"), PIPE));
	else if (!ft_strncmp("\'", cmd_line, 1))
		return (new_token(lex_single_quotes(cmd_line), SQUOTE));
	else if (!ft_strncmp("\"", cmd_line, 1))
		return (new_token(lex_double_quotes(cmd_line), DQUOTE));
	else
		return (new_token(lex_string(cmd_line), STRING));
}

static void	remove_string_quotations(t_node *tokens)
{
	t_token	*token;
	char	*tmp;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == DQUOTE || token->type == SQUOTE)
		{
			if (token->type == DQUOTE)
				tmp = ft_substr(token->value, 1, ft_strlen(token->value) - 2);
			else if (token->type == SQUOTE)
				tmp = ft_substr(token->value, 1, ft_strlen(token->value) - 2);
			free(token->value);
			token->value = tmp;
		}
		tokens = tokens->next;
	}
}

static char	*concat_quotes(char *str, char *quote)
{
	char *arr[4];

	arr[0] = quote; 
	arr[1] = str;
	arr[2] = quote;
	arr[3] = NULL;
	return (join_arr(arr, ""));
}

static void	return_string_quotations(t_node *tokens)
{
	t_token	*token;
	char	*tmp;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == DQUOTE || token->type == SQUOTE)
		{
			if (token->type == DQUOTE)
				tmp = concat_quotes(token->value, "\"");
			else if (token->type == SQUOTE)
				tmp = concat_quotes(token->value, "\'");
			free(token->value);
			token->value = tmp;
		}
		tokens = tokens->next;
	}
}

t_node	*tokenize(char *cmd_line)
{
	t_node	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (cmd_line[i])
	{
		if (ft_isspace(cmd_line[i]))
		{
			i++;
			continue ;
		}
		token = get_next_token(cmd_line + i);
		ll_push(&tokens, ll_new(token));
		if (token->type == ERR)
			break ;
		i += ft_strlen(token->value);
	}
	ll_push(&tokens, ll_new(new_token(NULL, END)));
	if (lexical_errors(tokens))
		return (ll_clear(&tokens, (void *)(void *)clear_token), NULL);
	remove_string_quotations(tokens);
	expand_envs(tokens);
	return_string_quotations(tokens);
	return (tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:37:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/26 14:17:52 by ekenane          ###   ########.fr       */
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
		return (new_token(lex_quotes(cmd_line, '\''), SQUOTE));
	else if (!ft_strncmp("\"", cmd_line, 1))
		return (new_token(lex_quotes(cmd_line, '\"'), DQUOTE));
	else if (!ft_strncmp(" ", cmd_line, 1) || !ft_strncmp("\t", cmd_line, 1))
		return (new_token(ft_strdup(" "), WSPACEE));
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
			token->type = STRING;
		}
		tokens = tokens->next;
	}
}

void	join_two_strings(t_node *current_node)
{
	char		*concatenate_value;
	t_token		*current;
	t_token		*next;
	t_node		*tmp;

	current = current_node->content;
	next = current_node->next->content;
	concatenate_value = ft_strjoin(current->value, next->value);
	free(current->value);
	free(next->value);
	free(next);
	tmp = current_node->next;
	current_node->next = current_node->next->next;
	free(tmp);
	current->value = concatenate_value;
	current_node->content = current;
}

void	join_string_tokens(t_node **tokens)
{
	t_node		*current_node;
	t_token		*current;
	t_token		*next;

	current_node = (*tokens);
	while (current_node->next)
	{
		current = current_node->content;
		next = current_node->next->content;
		if (current->type == STRING && next->type == STRING)
			join_two_strings(current_node);
		else
			current_node = current_node->next;
	}
	remove_space_tokens(tokens);
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
		token = get_next_token(cmd_line + i);
		ll_push(&tokens, ll_new(token));
		if (token->value == NULL)
		{
			return (ll_clear(&tokens, (void *)(void *)clear_token),
				werror("Unclosed Quotes!\n"), g_meta.status = 1, NULL);
		}
		i += ft_strlen(token->value);
	}
	ll_push(&tokens, ll_new(new_token(NULL, END)));
	expand_envs(tokens);
	remove_string_quotations(tokens);
	join_string_tokens(&tokens);
	if (lexical_errors(tokens))
		return (ll_clear(&tokens, (void *)(void *)clear_token),
			g_meta.status = 258, NULL);
	return (tokens);
}

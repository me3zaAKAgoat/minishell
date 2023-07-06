/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:37:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 22:06:55 by echoukri         ###   ########.fr       */
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
	else if (!ft_strncmp(" ", cmd_line, 1))
		return (new_token(ft_strdup(" "), SPACEE));
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

void	remove_space_tokens(t_node *head)
{
	t_node	*current_token;
	t_node	*previous_token;
	t_node	*next_token;
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		t_token		*token = tmp->content;
		printf("[%s]\n", token->value);
		tmp = tmp->next;
	}
	previous_token = head;
	current_token = head->next;
	while (current_token)
	{
		printf("here\n");
		current_token = previous_token->next;
		next_token = current_token->next;
		t_token		*pre_token = previous_token->content;
		t_token		*cu_token = current_token->content;
		t_token		*ne_token = next_token->content;
		printf("pre : {%s} | cu : {%s} | ne : {%s}\n", pre_token->value, cu_token->value, ne_token->value);
		if (cu_token->type == SPACEE)
		{
			previous_token->next = next_token;
			free(current_token);
			current_token = next_token;
		}
		else
			current_token = current_token->next;
		previous_token = previous_token->next;
	}
}
t_node	*tokenize(char *cmd_line)
{
	t_node	*tokens;
	t_node	*tmp_tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (cmd_line[i])
	{
		// if (ft_isspace(cmd_line[i]))
		// 	i++;
		// else
		// {
			token = get_next_token(cmd_line + i);
			ll_push(&tokens, ll_new(token));
			i += ft_strlen(token->value);
		// }
	}
	ll_push(&tokens, ll_new(new_token(NULL, END)));
	if (lexical_errors(tokens))
		return (ll_clear(&tokens, (void *)(void *)clear_token),
			g_meta.status = 1, NULL);
	remove_string_quotations(tokens);
	// joining tokens
	tmp_tokens = NULL;
	while (tokens->next)
	{
		char		*concatenate_value;
		t_token		*current_token = tokens->content;
		t_token		*next_token = tokens->next->content;
		if (current_token->type == STRING && next_token->type == STRING)
		{
			concatenate_value = ft_strjoin(current_token->value, next_token->value);
			ll_push(&tmp_tokens, ll_new(new_token(concatenate_value, STRING)));
		}
		else
			ll_push(&tmp_tokens, ll_new(new_token(current_token->value, current_token->type)));
		tokens = tokens->next;
	}
	// remove SPACE tokens
	remove_space_tokens(tmp_tokens);
	// while (tokens)
	// {
	// 	t_token		*token = tokens->content;
	// 	if (token->type == SPACEE)
	// 		printf("this token should be delete | value : [%s]\n", token->value);
	// 	tokens = tokens->next;
	// }
	// while (tmp_tokens)
	// {
	// 	t_token		*token = tmp_tokens->content;
	// 	printf("{%s}\n", token->value);
	// 	tmp_tokens = tmp_tokens->next;
	// }
	expand_envs(tokens);
	return (tokens);
}

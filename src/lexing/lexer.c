/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:37:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/04 21:33:01 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token(t_token *token)
{
	free(token->value);
	free(token);
}

static t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

static char	*lex_quotes(char *cmd_line, char delim)
{
	int		end;

	end = 0;
	while ((cmd_line + 1)[end] && (cmd_line + 1)[end] != delim)
		end++;
	return (ft_substr(cmd_line, 0, end + 2));
}

static char	*lex_string(char *cmd_line)
{
	int		end;

	end = 0;
	while (cmd_line[end] && !ft_isspace(cmd_line[end] && cmd_line[end] == '\'' && cmd_line[end] == '\"'))
		end++;
	return (ft_substr(cmd_line, 0, end));
}

static t_token	*get_next_token(char *cmd_line, int i)
{
	t_token	*token;

	if (cmd_line[i] == '\0')
		token = (new_token(ft_strdup(""), END));
	else if (!ft_strncmp("<<", cmd_line + i, 2))
		token = (new_token(ft_strdup("<<"), HEREDOC));
	else if (!ft_strncmp(">>", cmd_line + i, 2))
		token = (new_token(ft_strdup(">>"), APPEND));
	else if (!ft_strncmp("<", cmd_line + i, 1))
		token = (new_token(ft_strdup("<"), IN));
	else if (!ft_strncmp(">", cmd_line + i, 1))
		token = (new_token(ft_strdup(">"), OUT));
	else if (!ft_strncmp("|", cmd_line + i, 1))
		token = (new_token(ft_strdup("|"), PIPE));
	else if (!ft_strncmp("\'", cmd_line + i, 1))
		token = (new_token(lex_quotes(cmd_line + i, '\''), STRING));
	else if (!ft_strncmp("\"", cmd_line + i, 1))
		token = (new_token(lex_quotes(cmd_line + i, '\"'), STRING));
	else
		token = (new_token(lex_string(cmd_line + i), STRING));
	return (token);
}

t_node	*tokenize(char *cmd_line)
{
	t_node	*tokens;
	t_token *token;
	int		i;

	cmd_line = strip(cmd_line);
	tokens = NULL;
	i = 0;
	while (cmd_line[i])
	{
		if (ft_isspace(cmd_line[i]))
		{
			i++;
			continue;
		}
		token = get_next_token(cmd_line, i);
		ll_push(&tokens, ll_new(token));
		i += ft_strlen(token->value);
	}
	free(cmd_line);
	return (tokens);
}

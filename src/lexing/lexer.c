/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 03:37:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/05 03:06:25 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	end;

	end = 0;
	while (cmd_line[end] && (!ft_isspace(cmd_line[end])
			|| cmd_line[end] == '\'' || cmd_line[end] == '\"'))
		end++;
	return (ft_substr(cmd_line, 0, end));
}

static t_token	*get_next_token(char *cmd_line)
{
	if (*cmd_line == '\0')
		return (new_token(ft_strdup(""), END));
	else if (!ft_strncmp("<<", cmd_line, 2))
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
		return (new_token(lex_quotes(cmd_line, '\''), STRING));
	else if (!ft_strncmp("\"", cmd_line, 1))
		return (new_token(lex_quotes(cmd_line, '\"'), STRING));
	else
		return (new_token(lex_string(cmd_line), STRING));
}

static int	check_lexing_errors(t_node	*tokens)
{
	t_node	*iterator;
	t_token	*current;
	t_token	*next;

	iterator = tokens;
	while (iterator)
	{
		current = iterator->content;
		if ((current->type == OUT || current->type == IN))
		{
			if (!iterator->next)
				return (printf("parsing error near '%s'\n", current->value), 1);
			else
			{
				next = iterator->next->content;
				if (next->type != STRING)
					return (printf("parsing error near '%s'\n",
							current->value), 1);
			}
		}
		iterator = iterator->next;
	}
	return (0);
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
		i += ft_strlen(token->value);
	}
	if (check_lexing_errors(tokens))
		return (ll_clear(&tokens, clear_token), NULL);
	return (tokens);
}

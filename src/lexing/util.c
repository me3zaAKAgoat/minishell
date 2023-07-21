/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 03:14:08 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 23:28:10 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lex_quotes(char *cmd_line, char delim)
{
	int		end;

	end = 1;
	while (cmd_line[end] && cmd_line[end] != delim)
	{
		end++;
		if (!cmd_line[end])
			return (NULL);
	}
	return (ft_substr(cmd_line, 0, end + 1));
}

char	*lex_string(char *cmd_line)
{
	int	end;

	end = 0;
	while (cmd_line[end] && cmd_line[end] != '\''
		&& cmd_line[end] != '\"'
		&& cmd_line[end] != '|' && !ft_isspace(cmd_line[end]))
		end++;
	return (ft_substr(cmd_line, 0, end));
}

void	print_syntax_error(char *value)
{
	werror("Minishell: syntax error near unexpected token '");
	werror(value);
	werror("'\n");
}

int	syntax_error_pipe(t_token *current, t_node *iterator, int i)
{
	t_token	*next;

	if (i == 1)
		return (print_syntax_error(current->value), 1);
	next = iterator->next->content;
	if (next->type == END)
		return (print_syntax_error(current->value), 1);
	else if (!(STRING <= next->type && next->type <= SQUOTE)
		&& !(IN <= next->type && next->type <= APPEND))
		return (print_syntax_error(current->value), 1);
	return (0);
}

int	syntax_error_redirection(t_node *iterator, t_token *current)
{
	t_token	*next;

	if (!iterator->next)
		return (print_syntax_error(current->value), 1);
	else
	{
		next = iterator->next->content;
		if (!(STRING <= next->type && next->type <= SQUOTE))
			return (print_syntax_error(current->value), 1);
	}
	return (0);
}

int	lexical_errors(t_node	*tokens)
{
	t_node	*iterator;
	int		i;
	t_token	*current;

	iterator = tokens;
	i = 1;
	while (iterator)
	{
		current = iterator->content;
		// if (current->type == ERR)
		// 	return (print_syntax_error(current->value), 1);
		if (current->type == PIPE && syntax_error_pipe(current, iterator, i))
			return (1);
		else if (IN <= current->type && current->type <= APPEND
			&& syntax_error_redirection(iterator, current))
			return (1);
		i++;
		iterator = iterator->next;
	}
	return (0);
}

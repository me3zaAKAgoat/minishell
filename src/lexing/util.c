/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 03:14:08 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/29 21:02:13 by echoukri         ###   ########.fr       */
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

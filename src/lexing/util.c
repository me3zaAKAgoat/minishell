/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 03:14:08 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 04:56:22 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lex_quotes(char *cmd_line, char delim)
{
	int		end;

	end = 1;
	while (cmd_line[end] && cmd_line[end] != delim)
		end++;
	return (ft_substr(cmd_line, 0, end + 1));
}

char	*lex_string(char *cmd_line)
{
	int	end;

	end = 0;
	while (cmd_line[end] && cmd_line[end] != '\''
		&& cmd_line[end] != '\"' && !ft_isspace(cmd_line[end]))
		end++;
	return (ft_substr(cmd_line, 0, end));
}

int	lexical_errors(t_node	*tokens)
{
	t_node	*iterator;
	t_token	*current;
	t_token	*next;

	iterator = tokens;
	while (iterator)
	{
		current = iterator->content;
		if (current->type == ERR)
			return (werror("Minishell: Parsing error near '"),
				werror(current->value), werror("'\n"), 1);
		if (current->type == PIPE)
		{
			next = iterator->next->content;
			if (next->type == END)
				return (werror("Minishell: Parsing error near '"),
					werror(current->value), werror("'\n"), 1);
		}
		if (IN <= current->type && current->type <= APPEND)
		{
			if (!iterator->next)
				return (werror("Minishell: Parsing error near '"),
					werror(current->value), werror("'\n"), 1);
			else
			{
				next = iterator->next->content;
				if (!(STRING <= next->type && next->type <= SQUOTE))
					return (werror("Minishell: Parsing error near '"),
						werror(current->value), werror("'\n"), 1);
			}
		}
		iterator = iterator->next;
	}
	return (0);
}

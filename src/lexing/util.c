/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 03:14:08 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/20 03:15:24 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lex_double_quotes(char *cmd_line)
{
	int		end;

	end = 0;
	while ((cmd_line + 1)[end] && (cmd_line + 1)[end] != '\"')
		end++;
	return (ft_substr(cmd_line, 0, end + 2));
}

char	*lex_single_quotes(char *cmd_line)
{
	int		end;

	end = 0;
	while ((cmd_line + 1)[end] && (cmd_line + 1)[end] != '\'')
		end++;
	return (ft_substr(cmd_line, 0, end + 2));
}

char	*lex_string(char *cmd_line)
{
	int	end;

	end = 0;
	while (cmd_line[end] && !ft_isspace(cmd_line[end]))
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
		if (IN <= current->type && current->type <= APPEND)
		{
			if (!iterator->next)
				return (werror("Minishell: Parsing error near '"),
					werror(current->value), werror("'\n"), 1);
			else
			{
				next = iterator->next->content;
				if (next->type != STRING)
					return (werror("Minishell: Parsing error near '"),
						werror(current->value), werror("'\n"), 1);
			}
		}
		iterator = iterator->next;
	}
	return (0);
}

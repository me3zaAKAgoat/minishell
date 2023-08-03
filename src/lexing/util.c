/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 03:14:08 by echoukri          #+#    #+#             */
/*   Updated: 2023/08/02 16:34:36 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lex_quotes(char *cmd_line, char delim)
{
	int		end;

	end = 1;
	if (!cmd_line[end])
		return (NULL);
	while (cmd_line[end] && cmd_line[end] != delim)
	{
		end++;
		if (!cmd_line[end])
			return (NULL);
	}
	return (ft_substr(cmd_line, 0, end + 1));
}

int	is_special_token(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*lex_string(char *cmd_line)
{
	int	end;

	end = 0;
	while (cmd_line[end] 
		&& !is_special_token(cmd_line[end]) && !ft_isspace(cmd_line[end]))
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

char	*rm_expanded_extra_wspace(char *str, char *value)
{
	char	**arr_strs;

	arr_strs = ft_split(value, ' ');
	value = join_arr(arr_strs, " ");
	split_clear(arr_strs);
	str = append_to_result(str, ft_strdup(value));
	free(value);
	return (str);
}

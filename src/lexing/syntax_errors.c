/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:45:02 by ekenane           #+#    #+#             */
/*   Updated: 2023/07/21 14:47:07 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

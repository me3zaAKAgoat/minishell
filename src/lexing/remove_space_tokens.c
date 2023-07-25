/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:48:14 by ekenane           #+#    #+#             */
/*   Updated: 2023/07/21 14:48:30 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_one_space(t_node **head, t_node **previous, t_node **current)
{
	t_token	*current_token;

	current_token = (*current)->content;
	if ((*previous) == NULL)
	{
		*head = (*current)->next;
		free(current_token->value);
		free((*current)->content);
		free((*current));
		(*current) = *head;
	}
	else
	{
		(*previous)->next = (*current)->next;
		free(current_token->value);
		free((*current)->content);
		free((*current));
		(*current) = (*previous)->next;
	}
}

void	remove_space_tokens(t_node **head)
{
	t_node	*current_node;
	t_node	*previous_node;
	t_token	*current_token;

	current_node = *head;
	previous_node = NULL;
	while (current_node)
	{
		current_token = current_node->content;
		if (current_token->type == SPACEE)
			remove_one_space(head, &previous_node, &current_node);
		else
		{
			previous_node = current_node;
			current_node = current_node->next;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:10:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/16 03:11:42 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*get_cmds(t_node *tokens)
{
	t_node		*cmds;

	cmds = NULL;
	while (tokens)
	{
		ll_push(&cmds, ll_new(create_command(tokens)));
		while (((t_token *)tokens->content)->type != END
			&& ((t_token *)tokens->content)->type != PIPE)
			tokens = tokens->next;
		if (((t_token *)tokens->content)->type == END)
			break ;
		tokens = tokens->next;
	}
	return (cmds);
}

void	parse(t_meta *meta, char *cmd_line)
{
	t_node		*tokens;
	t_node		*cmds;

	(void)meta;
	if (!cmd_line)
		exit(0); // this should be status of last executed command instead of 0
	tokens = tokenize(cmd_line);
	if (!tokens)
		return ;
	cmds = get_cmds(tokens);
	if (!cmds)
		return ;
	ll_clear(&cmds, (void *)(void *)clear_command);
	ll_clear(&tokens, (void *)(void *)clear_token);
}

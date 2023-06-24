/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:10:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 23:03:47 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*get_cmds(t_node *tokens)
{
	t_node		*cmds;
	t_command	*cmd;

	cmds = NULL;
	while (((t_token *)tokens->content)->type != END)
	{
		cmd = create_command(tokens);
		if (cmd)
			ll_push(&cmds, ll_new(cmd));
		while (((t_token *)tokens->content)->type != END
			&& ((t_token *)tokens->content)->type != PIPE)
			tokens = tokens->next;
		if (((t_token *)tokens->content)->type == END)
			break ;
		tokens = tokens->next;
	}
	return (cmds);
}

void	parse(char *cmd_line)
{
	t_node		*tokens;
	t_node		*cmds;

	tokens = NULL;
	cmds = NULL;
	if (!cmd_line)
		exit(g_meta.status);
	tokens = tokenize(cmd_line);
	if (tokens)
	{
		cmds = get_cmds(tokens);
		if (cmds)
			execute_commands(cmds);
	}
	ll_clear(&cmds, (void *)(void *)clear_command);
	ll_clear(&tokens, (void *)(void *)clear_token);
}

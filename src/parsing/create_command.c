/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 02:38:45 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/16 02:41:36 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_command_args(t_node *tokens, t_command *cmd)
{
	char	*tmp;
	char	*args[3];

	tmp = cmd->args;
	if (!tmp)
		cmd->args = ft_strdup(((t_token *)tokens->content)->value);
	else
	{
		args[0] = tmp;
		args[1] = ((t_token *)tokens->content)->value;
		args[2] = NULL;
		cmd->args = join_arr(args, " ");
	}
	free(tmp);
}

void	setup_redirections(t_node *tokens, t_command *cmd)
{
	if (((t_token *)tokens->content)->type == IN)
	{
		tokens = tokens->next;
		cmd->infile = ft_strdup(((t_token *)tokens->content)->value);
	}
	else if (((t_token *)tokens->content)->type == OUT)
	{
		tokens = tokens->next;
		cmd->truncfile = ft_strdup(((t_token *)tokens->content)->value);
	}
	else if (((t_token *)tokens->content)->type == HEREDOC)
	{
		tokens = tokens->next;
		cmd->delim = ft_strdup(((t_token *)tokens->content)->value);
	}
	else if (((t_token *)tokens->content)->type == APPEND)
	{
		tokens = tokens->next;
		cmd->appendfile = ft_strdup(((t_token *)tokens->content)->value);
	}
}

t_command	*create_command(t_node *tokens)
{
	t_command	*cmd;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	while (((t_token *)tokens->content)->type != PIPE
		&& ((t_token *)tokens->content)->type != END)
	{
		if (IN <= ((t_token *)tokens->content)->type
			&& ((t_token *)tokens->content)->type <= APPEND)
		{
			setup_redirections(tokens, cmd);
			tokens = tokens->next->next;
		}
		while (((t_token *)tokens->content)->type != END
			&& (((t_token *)tokens->content)->type == STRING))
		{
			join_command_args(tokens, cmd);
			tokens = tokens->next;
		}
	}
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 02:38:45 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/22 02:30:26 by echoukri         ###   ########.fr       */
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

void	output_redirections(t_node *tokens, t_command *cmd)
{
	if (((t_token *)tokens->content)->type == OUT)
	{
		tokens = tokens->next;
		free(cmd->truncfile);
		free(cmd->appendfile);
		cmd->appendfile = NULL;
		cmd->truncfile = ft_strdup(((t_token *)tokens->content)->value);
	}
	else if (((t_token *)tokens->content)->type == APPEND)
	{
		tokens = tokens->next;
		free(cmd->appendfile);
		free(cmd->truncfile);
		cmd->truncfile = NULL;
		cmd->appendfile = ft_strdup(((t_token *)tokens->content)->value);
	}
}

void	input_redirections(t_node *tokens, t_command *cmd)
{
	if (((t_token *)tokens->content)->type == IN)
	{
		tokens = tokens->next;
		free(cmd->infile);
		free(cmd->delim);
		cmd->delim = NULL;
		cmd->infile = ft_strdup(((t_token *)tokens->content)->value);
	}
	else if (((t_token *)tokens->content)->type == HEREDOC)
	{
		tokens = tokens->next;
		free(cmd->delim);
		free(cmd->infile);
		cmd->infile = NULL;
		cmd->delim = ft_strdup(((t_token *)tokens->content)->value);
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
			input_redirections(tokens, cmd);
			output_redirections(tokens, cmd);
			tokens = tokens->next->next;
		}
		while (((t_token *)tokens->content)->type != END
			&& STRING <= (((t_token *)tokens->content)->type)
			&& (((t_token *)tokens->content)->type <= SQUOTE))
		{
			join_command_args(tokens, cmd);
			tokens = tokens->next;
		}
	}
	return (cmd);
}

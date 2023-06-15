/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:10:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/05 02:18:01 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_command	*create_command(t_node *tokens)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->args = NULL;
	cmd->appendfile = NULL;
	cmd->DELIM = NULL;
	cmd->truncfile = NULL;
	cmd->infile = NULL;
	if (!cmd)
		return (NULL);
	while (tokens && ((t_token *)tokens->content)->type != PIPE && ((t_token *)tokens->content)->type != END)
	{
		if (((t_token *)tokens->content)->type == IN)
		{
			tokens = tokens->next;
			cmd->infile = ((t_token *)tokens->content)->value;
			(tokens && (tokens = tokens->next));
		}
		else if (((t_token *)tokens->content)->type == OUT)
		{
			tokens = tokens->next;
			cmd->truncfile = ((t_token *)tokens->content)->value;
			(tokens && (tokens = tokens->next));
		}
		else if (((t_token *)tokens->content)->type == APPEND)
		{
			tokens = tokens->next;
			cmd->appendfile = ((t_token *)tokens->content)->value;
			(tokens && (tokens = tokens->next));
		}
		else if (((t_token *)tokens->content)->type == HEREDOC)
		{
			tokens = tokens->next;
			cmd->DELIM = ((t_token *)tokens->content)->value;
			(tokens && (tokens = tokens->next));
		}
		while (tokens && (((t_token *)tokens->content)->type == STRING || ((t_token *)tokens->content)->type == ENV))
		{
			char	*tmp = cmd->args;
			if (!tmp)
				cmd->args = ft_strdup(((t_token *)tokens->content)->value);
			else
			{
				char	*args[3];

				args[0] = tmp;
				args[1] = ((t_token *)tokens->content)->value;
				args[2] = NULL;
				cmd->args = array_to_str(args, " ");
			}
			free(tmp);
			tokens = tokens->next;
		}
	}
	return (cmd);
}

t_node	*get_cmds(t_node *tokens)
{
	t_node		*cmds;

	cmds = NULL;
	while (tokens)
	{
		ll_push(&cmds, ll_new(create_command(tokens)));
		while (tokens && ((t_token *)tokens->content)->type != END && ((t_token *)tokens->content)->type != PIPE)
			tokens = tokens->next;
		if (!tokens || ((t_token *)tokens->content)->type == END)
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
	while (cmds)
	{
		printf("%s\n", ((t_command *)cmds->content)->args);
		cmds = cmds->next;
	}
	ll_clear(&tokens, clear_token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 02:33:58 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/16 03:10:08 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->appendfile = NULL;
	cmd->delim = NULL;
	cmd->truncfile = NULL;
	cmd->infile = NULL;
	return (cmd);
}

void	clear_command(t_command *cmd)
{
	free(cmd->args);
	free(cmd->appendfile);
	free(cmd->delim);
	free(cmd->truncfile);
	free(cmd->infile);
	free(cmd);
}

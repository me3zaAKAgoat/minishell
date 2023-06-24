/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 05:19:14 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/24 07:23:24 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_redirection(t_command *cmd)
{
	if (cmd->infile == -1 || cmd->io_error)
		return ;
	dup2(cmd->infile, STDIN_FILENO);
	close(cmd->infile);
}

void	out_redirection(t_command *cmd)
{
	if (cmd->outfile == -1 || cmd->io_error)
		return ;
	dup2(cmd->outfile, STDOUT_FILENO);
	close(cmd->outfile);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 05:19:14 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 08:36:29 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_redirection(t_command *cmd)
{
	int		fd;
	char	*heredoc_filename;

	if (!cmd->infile && !cmd->delim)
		return ;
	if (cmd->infile)
		fd = open(cmd->infile, O_RDONLY);
	else if (cmd->delim)
	{
		heredoc_filename = here_doc(cmd->delim);
		if (!heredoc_filename)
			fd = -1;
		else
		{
			fd = open(heredoc_filename, O_RDONLY);
			unlink(heredoc_filename);
			free(heredoc_filename);
		}
	}
	if (fd == -1)
	{
		perror("Minishell");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	out_redirection(t_command *cmd)
{
	int	fd;

	if (!cmd->appendfile && !cmd->truncfile)
		return ;
	if (cmd->truncfile)
		fd = open(cmd->truncfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->appendfile)
		fd = open(cmd->appendfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Minishell");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

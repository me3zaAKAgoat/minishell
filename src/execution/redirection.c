/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 05:19:14 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 17:06:40 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_heredoc(char *delim)
{
	char	*heredoc_filename;
	int		fd;

	heredoc_filename = here_doc(delim);
	if (!heredoc_filename)
		fd = -1;
	else
	{
		fd = open(heredoc_filename, O_RDONLY);
		unlink(heredoc_filename);
		free(heredoc_filename);
	}
	return (fd);
}

int	input_redirection(t_command *cmd)
{
	int		fd;

	fd = -1;
	if (!cmd->infile && !cmd->delim)
		return (0);
	if (cmd->infile)
		fd = open(cmd->infile, O_RDONLY);
	else if (cmd->delim)
		fd = open_heredoc(cmd->delim);
	if (fd == -1)
		return (perror("Minishell: Input Redirection"), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	out_redirection(t_command *cmd)
{
	int	fd;

	fd = -1;
	if (!cmd->appendfile && !cmd->truncfile)
		return (0);
	if (cmd->truncfile)
		fd = open(cmd->truncfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->appendfile)
		fd = open(cmd->appendfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("Minishell: Output Redirection"), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

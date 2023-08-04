/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 05:17:50 by echoukri          #+#    #+#             */
/*   Updated: 2023/08/03 15:03:06 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes(int first_pipe[2], int second_pipe[2])
{
	if (first_pipe && !second_pipe)
	{
		close(first_pipe[READ_END]);
		dup2(first_pipe[WRITE_END], STDOUT_FILENO);
		close(first_pipe[WRITE_END]);
	}
	else if (!first_pipe && second_pipe)
	{
		close(second_pipe[WRITE_END]);
		dup2(second_pipe[READ_END], STDIN_FILENO);
		close(second_pipe[READ_END]);
	}
	else if (first_pipe && second_pipe)
	{
		dup2(first_pipe[READ_END], STDIN_FILENO);
		close(first_pipe[READ_END]);
		close(second_pipe[READ_END]);
		dup2(second_pipe[WRITE_END], STDOUT_FILENO);
		close(second_pipe[WRITE_END]);
	}
}

void	close_pipes(int first_pipe[2], int second_pipe[2])
{
	if (first_pipe && !second_pipe)
		close(first_pipe[WRITE_END]);
	else if (!first_pipe && second_pipe)
		close(second_pipe[READ_END]);
	else if (first_pipe && second_pipe)
	{
		close(first_pipe[READ_END]);
		close(second_pipe[WRITE_END]);
	}
}

void	pipeline(t_node *cmds)
{
	int	*pipefd;
	int	i;

	pipefd = malloc((ll_size(cmds) - 1) * 2 * sizeof(int));
	if (!pipefd)
		return ;
	i = 0;
	while (ll_size(cmds))
	{
		if (i == 0)
		{
			pipe(pipefd);
			cmd_wrapper(cmds->content, pipefd, NULL);
		}
		else if (ll_size(cmds) > 1)
		{
			pipe(pipefd + i * 2);
			cmd_wrapper(cmds->content, pipefd + (i - 1) * 2, pipefd + i * 2);
		}
		else
			cmd_wrapper(cmds->content, NULL, pipefd + (i - 1) * 2);
		cmds = cmds->next;
		i++;
	}
	free(pipefd);
}

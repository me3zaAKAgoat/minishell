/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 03:46:51 by echoukri          #+#    #+#             */
/*   Updated: 2023/08/05 16:40:16 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_command *cmd)
{
	char	**envp;

	if (cmd->io_error)
		exit(EXIT_FAILURE);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	envp = envp_generator(g_meta.env);
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK))
			(perror("Minishell"), exit(CMD_UNKNOWN));
		execve(cmd->args[0], cmd->args, envp);
		(werror("Minishell: "), werror(cmd->args[0]), perror(" "));
		exit(CMD_FAIL);
	}
	else if (is_builtin(cmd))
		(handle_builtin(cmd), exit(g_meta.status));
	else
		handle_bin_cmd(cmd->args, envp);
	free_envp(envp);
}

void	handle_priority(t_command *cmd, int **first_pipe, int **second_pipe)
{
	if (cmd->infile >= 0)
		*second_pipe = NULL;
	if (cmd->outfile >= 0)
		*first_pipe = NULL;
}

/*
redirections have priority over pipes that's why the pipes get nullifyed if
there's a redirection
*/
void	cmd_wrapper(t_command *cmd, int first_pipe[2], int second_pipe[2])
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t));
	if (!pid)
		return ;
	*pid = fork();
	if (*pid == 0)
	{
		execution_signals();
		input_redirection(cmd);
		out_redirection(cmd);
		handle_priority(cmd, &first_pipe, &second_pipe);
		setup_pipes(first_pipe, second_pipe);
		exec_cmd(cmd);
	}
	else
	{
		if (*pid < 0)
			perror("Minishell: Command execution:");
		else
			ll_push(&g_meta.pids, ll_new(pid));
		close_pipes(first_pipe, second_pipe);
	}
}

void	single_command(t_command *cmd)
{
	int	original_stdin;
	int	original_stdout;

	if (is_builtin(cmd))
	{
		original_stdin = dup(0);
		original_stdout = dup(1);
		input_redirection(cmd);
		out_redirection(cmd);
		if (!cmd->io_error)
			handle_builtin(cmd);
		else
			g_meta.status = EXIT_FAILURE;
		dup2(original_stdin, 0);
		dup2(original_stdout, 1);
		close(original_stdin);
		close(original_stdout);
	}
	else
		cmd_wrapper(cmd, NULL, NULL);
}

/*
the break in the loop is a check
for whether the sigint handler has killed all the pids already
*/
void	execute_commands(t_node *cmds)
{
	int		status;

	if (ll_size(cmds) == 1)
		single_command(cmds->content);
	else if (ll_size(cmds) > 1)
		pipeline(cmds);
	while (ll_size(g_meta.pids))
	{
		waitpid(*((pid_t *)g_meta.pids->content), &status, 0);
		if (WIFSIGNALED(status))
			g_meta.status = CMD_SIGNALED + WTERMSIG(status);
		else if (WIFEXITED(status))
			g_meta.status = WEXITSTATUS(status);
		ll_del_one(ll_shift(&g_meta.pids), free);
	}
}

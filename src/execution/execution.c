/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 03:46:51 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/19 13:54:46 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_command *cmd)
{
	char	**args;
	char	**envp;

	args = ft_split(cmd->args, ' ');
	envp = envp_generator(g_meta.env);
	if (ft_strnstr(args[0], "/", ft_strlen(args[0])) && !access(args[0], F_OK))
	{
		execve(args[0], args, envp);
		perror("Minishell: Script execution:");
		exit(1);
	}
	else
	{
		if (!handle_non_redirectable_builtin(args) && !handle_redirectable_builtin(args))
			handle_bin_cmd(args, envp);
	}
	split_clear(args);
	free_envp(envp);
}

void	cmd_wrapper(t_command *cmd, int first_pipe[2], int second_pipe[2])
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t));
	if (!pid)
		return ; // handle errors
	*pid = fork();
	if (!*pid)
	{
		input_redirection(cmd);
		out_redirection(cmd);
		setup_pipes(first_pipe, second_pipe);
		if (cmd->args)
			exec_cmd(cmd);
		exit(0);
	}
	else if (*pid < 0)
	{
		perror("Minishell: Command execution:");
		close_pipes(first_pipe, second_pipe);
	}
	else
	{
		close_pipes(first_pipe, second_pipe);
		ll_push(&g_meta.pids, ll_new(pid));
	}
}

void	one_command(t_node *cmds)
{
	char	**args;

	args = ft_split(((t_command *)cmds->content)->args, ' ');
	if (!handle_non_redirectable_builtin(args))
		cmd_wrapper(cmds->content, NULL, NULL);
	split_clear(args);
}

/*
the break in the loop is a check
for whether the sigint handler has killed all the pids already
*/
void	execute_commands(t_node *cmds)
{
	int		status;

	if (ll_size(cmds) == 1)
		one_command(cmds);
	else if (ll_size(cmds) > 1)
		pipeline(cmds);
	while (ll_size(g_meta.pids))
	{
		waitpid(*((pid_t *)g_meta.pids->content), &status, 0);
		if (WIFEXITED(status))
			g_meta.status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_meta.status = 127 + WTERMSIG(status);
		if (!ll_size(g_meta.pids))
			break ;
		ll_del_one(ll_shift(&g_meta.pids), free);
		continue ;
	}
}

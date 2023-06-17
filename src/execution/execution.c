/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 03:46:51 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 03:02:25 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_pathenv(char	*envp[])
{
	char	**paths;
	char	**tmp;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", ft_strlen("PATH")))
		{
			tmp = ft_split(*envp, '=');
			paths = ft_split(tmp[1], ':');
			split_clear(tmp);
			return (paths);
		}
		envp++;
	}
	return (NULL);
}

char	*get_cmdpath(char	**paths, char	*cmd)
{
	char	*command;
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	input_redirection(t_command *cmd)
{
	int	fd;

	if (!cmd->infile && !cmd->delim)
		return ;
	if (cmd->infile)
		fd = open(cmd->infile, O_RDONLY);
	else if (cmd->delim)
		fd = here_doc(cmd->delim);
	if (fd == -1)
	{
		perror("");
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
		fd = open(cmd->truncfile, O_WRONLY | O_TRUNC);
	else if (cmd->appendfile)
		fd = open(cmd->appendfile, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		perror("");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);	
}

void	handle_bin_cmd(char **args, char **envp)
{
	char	**paths;
	char	*cmd_path;

	paths = get_pathenv(envp);
	if (!paths)
	{
		write(2, "error handling bin command", ft_strlen("error handling bin command"));
		exit(1);
	}
	cmd_path = get_cmdpath(paths, args[0]);	
	if (!cmd_path)
	{
		write(2, "Command ", ft_strlen("Command "));
		write(2, args[0], ft_strlen(args[0]));
		write(2, " not found.", ft_strlen(" not found."));
		split_clear(paths);
		exit(CMD_UNKNOWN);
	}
	execve(cmd_path, args, envp);
	perror("");
	exit(1);
}

void	exec_cmd(t_command *cmd)
{
	char	**args;
	char	**envp;

	args = ft_split(cmd->args, ' ');
	envp = envp_generator(g_meta.env);
	if (ft_strnstr(args[0], "/", ft_strlen(args[0])) && !access(args[0], F_OK))
	{
		execve("/usr/bin/bash", args, envp);
		perror("");
		exit(1);
	}
	else
	{
		handle_builtin(args);
		handle_bin_cmd(args, envp);
	}
	split_clear(args);
	free_envp(envp);
}

void	setup_pipes(int first_pipe[2], int second_pipe[2])
{
	if (first_pipe && !second_pipe)
	{
		dup2(first_pipe[WRITE_END], STDOUT_FILENO);
		close(first_pipe[WRITE_END]);	
	}
	else if (!first_pipe && second_pipe)
	{
		dup2(first_pipe[READ_END], STDIN_FILENO);
		close(first_pipe[READ_END]);	
	}
	else if (first_pipe && second_pipe)
	{
		dup2(first_pipe[READ_END], STDIN_FILENO);
		close(first_pipe[READ_END]);
		dup2(second_pipe[WRITE_END], STDOUT_FILENO);
		close(second_pipe[WRITE_END]);
	}
}

void	close_pipes(int first_pipe[2], int second_pipe[2])
{
	if (first_pipe && !second_pipe)
	{
		close(first_pipe[WRITE_END]);	
	}
	else if (!first_pipe && second_pipe)
	{
		close(first_pipe[READ_END]);	
	}
	else if (first_pipe && second_pipe)
	{
		close(first_pipe[READ_END]);
		close(second_pipe[WRITE_END]);
	}
}

void	cmd_wrapper(t_command *cmd, int first_pipe[2], int second_pipe[2])
{
	pid_t	*pid;
	
	pid	= malloc(sizeof(pid));
	*pid = fork();
	if (!*pid)
	{
		input_redirection(cmd);
		out_redirection(cmd);
		setup_pipes(first_pipe, second_pipe);
		exec_cmd(cmd);
	}
	else if (*pid < 0)
	{
		//error handling
	}
	else
	{
		close_pipes(first_pipe, second_pipe);
		ll_push(&g_meta.pids, ll_new(pid));
	}
}

void	pipeline(t_node *cmds)
{
	int	*pipefd;
	int	i;

	pipefd = malloc((ll_size(cmds) - 1) * sizeof(int));
	i = 0;
	while (ll_size(cmds))
	{
		if (i == 0)
		{
			pipe(pipefd);
			cmd_wrapper(cmds->content, pipefd, NULL);			
		}
		else if (ll_size(cmds) != 1)
		{
			pipe(pipefd + i * 2);
			pipe(pipefd + (i + 1) * 2);
			cmd_wrapper(cmds->content, pipefd + i * 2, pipefd + (i + 1) * 2);
		}
		else
			cmd_wrapper(cmds->content, NULL, pipefd + (i + 1) * 2);
		cmds = cmds->next;
		i++;
	}
}

void	execute_commands(t_node *cmds)
{
	int	status;

	if (ll_size(cmds) == 1)
		cmd_wrapper(cmds->content, NULL, NULL);
	else if (ll_size(cmds) > 1)
		pipeline(cmds);
	while (ll_size(g_meta.pids) && waitpid(*((pid_t *)g_meta.pids->content), &status, 0))
	{
		if (WIFEXITED(status))
			g_meta.status = WEXITSTATUS(status);
		ll_del_one(ll_shift(&g_meta.pids), free);
		continue;
	}
}
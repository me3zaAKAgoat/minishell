/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 05:26:18 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 22:07:10 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_pathenv(char	*envp[])
{
	char	**paths;
	char	**tmp;

	while (envp && *envp)
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

void	handle_bin_cmd(char **args, char **envp)
{
	char	**paths;
	char	*cmd_path;

	paths = get_pathenv(envp);
	if (!paths)
		(werror("Minishell: Could not get command paths.\n"), exit(1));
	cmd_path = get_cmdpath(paths, args[0]);
	if (!cmd_path)
		(werror("Minishell: Command not found: "), werror(args[0]),
			werror("\n"), split_clear(paths), exit(CMD_UNKNOWN));
	execve(cmd_path, args, envp);
	(perror("Minishell: Bin command:"), exit(CMD_FAIL));
}

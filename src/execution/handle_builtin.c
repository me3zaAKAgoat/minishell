/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 03:44:59 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/22 18:47:16 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->args)
		return (0);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	return (0);
}

void	handle_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->args[0], "exit"))
		shell_exit(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		cd(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		echo(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "export"))
		export(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "env"))
		print_env(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset(cmd->args);
}

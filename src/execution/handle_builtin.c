/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 03:44:59 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/25 17:51:51 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->args || !cmd->args[0])
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
		ft_exit(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd->args);
}

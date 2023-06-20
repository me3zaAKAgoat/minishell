/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 03:44:59 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/20 15:57:03 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	char	**args;

	if (!cmd->args)
		return (0);
	args = ft_split(cmd->args, ' ');
	if (!ft_strcmp(args[0], "exit"))
		return (split_clear(args), 1);
	else if (!ft_strcmp(args[0], "cd"))
		return (split_clear(args), 1);
	else if (!ft_strcmp(args[0], "echo"))
		return (split_clear(args), 1);
	else if (!ft_strcmp(args[0], "pwd"))
		return (split_clear(args), 1);
	else if (!ft_strcmp(args[0], "export"))
		return (split_clear(args), 1);
	else if (!ft_strcmp(args[0], "env"))
		return (split_clear(args), 1);
	else if (!ft_strcmp(args[0], "unset"))
		return (split_clear(args), 1);
	return (split_clear(args), 0);
}

void	handle_builtin(t_command *cmd)
{
	char	**args;

	args = ft_split(cmd->args, ' ');
	if (!ft_strcmp(args[0], "exit"))
		shell_exit(args);
	else if (!ft_strcmp(args[0], "cd"))
		cd(args);
	else if (!ft_strcmp(args[0], "echo"))
		echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		pwd(args);
	else if (!ft_strcmp(args[0], "export"))
		export(args);
	else if (!ft_strcmp(args[0], "env"))
		print_env(args);
	else if (!ft_strcmp(args[0], "unset"))
		unset(args);
	split_clear(args);
}

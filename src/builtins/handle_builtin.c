/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 03:44:59 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 09:08:29 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirectable_builtin(char **args)
{
	(void)args;
// echo
	return (0);
}

int	handle_non_redirectable_builtin(char **args)
{
	if (!ft_strcmp(args[0], "exit"))
		return (shell_exit(args), 1);
	else if (!ft_strcmp(args[0], "cd"))
		return (cd(args), 1);
	else if (!ft_strcmp(args[0], "env"))
		return (print_env(args), 1);
	else if (!ft_strcmp(args[0], "export"))
		return (export(args), 1);
	else if (!ft_strcmp(args[0], "unset"))
		return (unset(args), 1);
	else if (!ft_strcmp(args[0], "pwd"))
		return (pwd(args), 1);
	return (0);
}

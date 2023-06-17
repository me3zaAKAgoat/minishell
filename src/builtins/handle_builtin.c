/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 03:44:59 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 07:50:44 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin(char **args)
{
	if (!ft_strcmp(args[0], "exit"))
		shell_exit(args);
	else if (!ft_strcmp(args[0], "cd"))
		cd(args);
	else if (!ft_strcmp(args[0], "env"))
		print_env(args);
	else if (!ft_strcmp(args[0], "export"))
		export(args);
	else if (!ft_strcmp(args[0], "unset"))
		unset(args);
	else if (!ft_strcmp(args[0], "pwd"))
		pwd(args);
}

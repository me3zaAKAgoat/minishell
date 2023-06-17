/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 03:44:59 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 06:33:45 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin(char **args)
{
	if (!ft_strncmp(args[0], "exit", ft_strlen(args[0])))
		shell_exit(args);
	else if (!ft_strncmp(args[0], "cd", ft_strlen(args[0])))
		cd(args);
	else if (!ft_strncmp(args[0], "env", ft_strlen(args[0])))
		print_env(args);
	else if (!ft_strncmp(args[0], "export", ft_strlen(args[0])))
		export(args);
	else if (!ft_strncmp(args[0], "unset", ft_strlen(args[0])))
		unset(args);
	else if (!ft_strncmp(args[0], "pwd", ft_strlen(args[0])))
		pwd(args);
}

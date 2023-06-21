/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:31:02 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/21 20:14:33 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exit(char **args)
{
	(void)args;
	if (!args[1])
		exit(g_meta.status);
	else if (args[2])
		werror("Minishell: exit: too many arguments.\n");
	else if (!is_number(args[1])
		|| ft_atoul(args[1]) < LONG_MAX || LONG_MIN < ft_atoul(args[1]))
	{
		werror("exit\n");
		werror("Minishell: exit: ");
		werror(args[1]);
		werror(" numeric argument required.\n");
		exit(BUILTIN_INCORRECT_USAGE);
	}
	else
		exit(ft_atoul(args[1]));
}

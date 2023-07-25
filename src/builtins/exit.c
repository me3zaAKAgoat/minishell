/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:31:02 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/28 20:03:32 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bad_argument_exit(char **args)
{
	printf("exit\n");
	werror("Minishell: exit: ");
	werror(args[1]);
	werror(": numeric argument required\n");
	// should be exit with 255 not 2
	// exit(BUILTIN_INCORRECT_USAGE);
	exit(255);
}

void	ft_exit(char **args)
{	
	if (!args[1])
		(printf("exit\n"), exit(g_meta.status));
	else if (!is_number(args[1])
		|| ((ft_atoll(args[1]) && !ft_atoll(args[1])) || errno == EOVERFLOW))
		bad_argument_exit(args);
	else if (args[2])
	{
		g_meta.status = BUILTIN_FAIL;
		werror("Minishell: exit: too many arguments\n");
	}
	else
		(printf("exit\n"), exit(ft_atoll(args[1])));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:54:19 by ekenane           #+#    #+#             */
/*   Updated: 2023/06/23 01:54:59 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * skip the first arg, always "echo"
 * handle first option (only one that matters)
 * skip all other valid options
 * while there are non option arguments, print them,
 *  if there's an additional argument, print space
 * check newline
*/

int	should_suppress_newline(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (arg[i] == '-')
	{
		i++;
		if (!arg[i])
			return (0);
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char **args)
{
	int	suppress_newline;

	args++;
	suppress_newline = should_suppress_newline(*args);
	while (*args && should_suppress_newline(*args))
		args++;
	while (*args)
	{
		printf("%s", *args);
		if (*(args + 1))
			printf(" ");
		args++;
	}
	if (!suppress_newline)
		printf("\n");
	g_meta.status = 0;
}

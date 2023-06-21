/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:54:19 by ekenane           #+#    #+#             */
/*   Updated: 2023/06/20 16:03:39 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_without_args(char **args)
{
	if (!args[1])
		return (printf("\n"), 1);
	return (0);
}

int	new_line_option_valid(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i += 1;
	else
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	new_line_option(char **args, int *i)
{
	int	print_new_line;

	(*i) = 1;
	print_new_line = 1;
	while (args[(*i)])
	{
		if (new_line_option_valid(args[(*i)]))
			print_new_line = 0;
		else
			break ;
		(*i)++;
	}
	return (print_new_line);
}

void	print_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			printf("%d", g_meta.status);
			i += 2;
		}
		else
		{
			printf("%c", arg[i]);
			i++;
		}
	}
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		print_arg(args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

void	echo(char **args)
{
	int	i;
	int	print_new_line;

	// NB: [-n option] should be outside a double/single quotes to works
	if (echo_without_args(args))
		return ;
	print_new_line = new_line_option(args, &i);
	print_args(args + i);
	if (print_new_line)
		printf("\n");
	return ;
}

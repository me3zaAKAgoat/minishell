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
	{
		printf("\n");
		return(1);
	}
	return(0);
}

int	new_line_option(char **args, int *i)
{
	int	print_new_line;

	(*i) = 1;
	print_new_line = 1;
	while (args[(*i)])
	{
		if (!ft_strcmp(args[(*i)], "-n"))
			print_new_line = 0;
		else
			break;
		(*i)++;
	}
	return (print_new_line);
}

void	print_args(char **args)
{
	int i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

void	echo(char **args)
{
	int	i;
	int	print_new_line;

	if (echo_without_args(args))
		return ;
	// NB: -n should be outside a double/single quotes to works
	print_new_line = new_line_option(args, &i);
	print_args(args + i);
	if (print_new_line)
		printf("\n");
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:30:57 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 22:05:56 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		perror("Minishell: pwd");
		g_meta.status = BUILTIN_FAIL;
	}
	else
	{
		write(1, wd, ft_strlen(wd));
		free(wd);
		write(1, "\n", 1);
		g_meta.status = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:30:57 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/22 20:05:13 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **args)
{
	char	*wd;

	(void)args;
	wd = getcwd(NULL, 0);
	write(1, wd, ft_strlen(wd));
	free(wd);
	write(1, "\n", 1);
	g_meta.status = 0;
}

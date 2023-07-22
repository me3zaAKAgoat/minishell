/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:30:57 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/22 21:39:57 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*wd;
	t_dict	*kvp;

	g_meta.status = 0;
	wd = getcwd(NULL, 0);
	if (!wd)
	{
		kvp = get_kvp(g_meta.env, "PWD");
		if (kvp && kvp->value)
			write(1, kvp->value, ft_strlen(kvp->value));
		else
		{
			g_meta.status = BUILTIN_FAIL;
			werror("error retrieving current directory");
		}
	}
	else
	{
		write(1, wd, ft_strlen(wd));
		free(wd);
	}
	write(1, "\n", 1);
}

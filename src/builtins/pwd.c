/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:30:57 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 18:59:49 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*wd;
	t_dict	*kvp;
		
	wd = getcwd(NULL, 0);
	// if (wd = NULL) print the PWD
	if (!wd)
	{
		kvp = get_kvp(g_meta.env, "PWD");
		write(1, kvp->value, ft_strlen(kvp->value));
		write(1, "\n", 1);
	}
	else
	{
		write(1, wd, ft_strlen(wd));
		free(wd);
		write(1, "\n", 1);
	}
		g_meta.status = 0;
}

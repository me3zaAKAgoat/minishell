/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:30:57 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/27 19:50:50 by echoukri         ###   ########.fr       */
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
		if (kvp)
			write(1, kvp->value, ft_strlen(kvp->value));
	}
	else
	{
		write(1, wd, ft_strlen(wd));
		free(wd);
	}
	write(1, "\n", 1);
}

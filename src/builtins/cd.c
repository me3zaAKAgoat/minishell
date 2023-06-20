/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:27:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/20 02:06:00 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_wd(char *key)
{
	t_dict	*kvp;
	char	*cwd;

	kvp = get_kvp(g_meta.env, key);
	free(kvp->value);
	cwd = getcwd(NULL, 0);
	kvp->value = ft_strdup(cwd);
	free(cwd);
}

void	cd(char **args)
{
	char	*dir;
	t_dict	*kvp;

	if (!args[1])
	{
		kvp = get_kvp(g_meta.env, "HOME");
		if (!kvp)
			return ;
		dir = kvp->value;
	}
	else
		dir = args[1];
	update_env_wd("OLDPWD");
	if (chdir(dir) == -1)
		perror("Minishell: cd");
	else
		update_env_wd("PWD");
}

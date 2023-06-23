/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:27:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 18:54:38 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_dirs(char *key)
{
	t_dict	*kvp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	kvp = get_kvp(g_meta.env, key);
	if (!kvp)
	{
		kvp->value = ft_strdup(cwd);
		ll_push(&g_meta.env, ll_new(kvp));
	}
	else
	{
		free(kvp->value);
		kvp->value = ft_strdup(cwd);
	}
	free(cwd);
}

void	too_many_args(void)
{
	werror("Minishell: cd: too many arguments\n");
	g_meta.status = BUILTIN_FAIL;
}

void	ft_cd(char **args)
{
	char	*dir;
	t_dict	*kvp;

	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		kvp = get_kvp(g_meta.env, "HOME");
		if (!kvp)
			return ;
		dir = kvp->value;
	}
	else if (args[2])
		return (too_many_args());
	else
		dir = args[1];
	update_env_dirs("OLDPWD");
	if (chdir(dir) == -1)
	{
		perror("Minishell: cd");
		g_meta.status = BUILTIN_FAIL;
	}
	else
		update_env_dirs("PWD");
}

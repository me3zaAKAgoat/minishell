/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:27:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/27 20:15:04 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/errno.h>

void	update_env_dirs(char *key, char *dir)
{
	t_dict	*kvp;
	t_dict	*kvp_pwd;
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("Minishell: cd ");
	kvp = get_kvp(g_meta.env, key);
	if (!cwd && kvp && !ft_strcmp(key, "PWD"))
	{
		tmp = kvp->value;
		kvp->value = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = kvp->value;
		kvp->value = ft_strjoin(tmp, dir);
		free(tmp);
	}
	else if (!cwd && kvp && !ft_strcmp(key, "OLDPWD"))
	{
		kvp_pwd = get_kvp(g_meta.env, "PWD");
		if (!kvp_pwd)
			return ;
		free(kvp->value);
		kvp->value = ft_strdup(kvp_pwd->value);
	}
	else if (!kvp)
	{
		kvp = new_kvp(key, ft_strdup(cwd));
		ll_push(&g_meta.env, ll_new(kvp));
	}
	else
	{
		free(kvp->value);
		kvp->value = ft_strdup(cwd);
	}
	free(cwd);
}

char	*next_dir(char *arg)
{
	t_dict	*kvp;
	char	*home;

	if (!arg || arg[0] == '~')
	{
		kvp = get_kvp(g_meta.env, "HOME");
		if (kvp)
			home = kvp->value;
		else
			return (g_meta.status = BUILTIN_FAIL,
				werror("Minishell: cd: HOME not set"), NULL);
	}
	if (!arg || (arg[0] == '~' && ft_strlen(arg) == 1))
		return (ft_strdup(home));
	else if (arg[0] == '~' && ft_strlen(arg) > 1)
		return (ft_strjoin(home, arg + 1));
	else
		return (ft_strdup(arg));
}

void	ft_cd(char **args)
{
	char	*dir;

	g_meta.status = 0;
	dir = next_dir(args[1]);
	if (!dir)
		return ;
	update_env_dirs("OLDPWD", dir);
	if (chdir(dir) == 0)
		update_env_dirs("PWD", dir);
	else
		(g_meta.status = BUILTIN_FAIL, perror("Minishell: cd"));
	free(dir);
}

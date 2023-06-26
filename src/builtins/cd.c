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
#include <sys/errno.h>

void	update_env_dirs(char *key, char *dir)
{
	t_dict	*kvp;
	t_dict	*kvp_pwd;
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	kvp = get_kvp(g_meta.env, key);
	if (!cwd && kvp && !ft_strcmp(key, "PWD"))
	{
		g_meta.status = 0;
		perror("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
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

void	ft_cd(char **args)
{
	(void)args;
	char	*dir;
	char	*tmp_without_home;
	char	*tmp_with_home;
	t_dict	*kvp;

	if (!args[1] || !ft_strncmp(args[1], "~", 1))
	{
		kvp = get_kvp(g_meta.env, "HOME");
		if (!kvp)
		{
			write (1, "bash: cd: HOME not set", ft_strlen("bash: cd: HOME not set"));
			write(1, "\n", 1);
			g_meta.status = BUILTIN_FAIL;
			return ;
		}
		else if (args[1] && ft_strcmp(args[1], "~"))
		{
			tmp_without_home = ft_strtrim(args[1], "~");
			tmp_with_home = ft_strjoin(kvp->value, tmp_without_home);
			dir = tmp_with_home;
			free(tmp_without_home);
			free(tmp_with_home);
		}
		else
			dir = kvp->value;
	}
	else
		dir = args[1];
	update_env_dirs("OLDPWD", dir);
	if (chdir(dir) == -1)
	{
		// should print name of this dir (bash: cd: 3t5536: No such file or directory)
		perror("Minishell: cd");
		g_meta.status = BUILTIN_FAIL;
	}
	else
		update_env_dirs("PWD", dir);
}

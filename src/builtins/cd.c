/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:27:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/25 16:05:36 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_new_value(t_dict **kvp_old_pwd)
{
	t_dict	*kvp_pwd;

	kvp_pwd = get_kvp(g_meta.env, "PWD");
	free((*kvp_old_pwd)->value);
	if (!kvp_pwd)
		(*kvp_old_pwd)->value = ft_strdup("");
	else
		(*kvp_old_pwd)->value = ft_strdup(kvp_pwd->value);
}

void	update_old_pwd(char *cwd)
{
	t_dict	*kvp_old_pwd;

	kvp_old_pwd = get_kvp(g_meta.env, "OLDPWD");
	if (kvp_old_pwd)
		set_new_value(&kvp_old_pwd);
	else if (!kvp_old_pwd && g_meta.flags.set_old_pwd == 0)
	{
		g_meta.flags.set_old_pwd = 1;
		kvp_old_pwd = new_kvp("OLDPWD", cwd);
		ll_push(&g_meta.env, ll_new(kvp_old_pwd));
	}
	else if (!kvp_old_pwd && g_meta.flags.set_old_pwd == 1)
		return ;
	else
	{
		free(kvp_old_pwd->value);
		kvp_old_pwd->value = ft_strdup(cwd);
	}
}

void	update_pwd(char *dir, char *cwd)
{
	t_dict	*kvp_pwd;
	char	*tmp;

	if (!cwd)
		perror("Minishell: cd ");
	kvp_pwd = get_kvp(g_meta.env, "PWD");
	if (!kvp_pwd)
		return ;
	else if (!cwd && kvp_pwd)
	{
		tmp = kvp_pwd->value;
		kvp_pwd->value = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = kvp_pwd->value;
		kvp_pwd->value = ft_strjoin(tmp, dir);
		free(tmp);
	}
	else
	{
		free(kvp_pwd->value);
		kvp_pwd->value = ft_strdup(cwd);
	}
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
				werror("Minishell: cd: HOME not set\n"), NULL);
	}
	if (!arg || (arg[0] == '~' && ft_strlen(arg) == 1))
		return (ft_strdup(home));
	else if (arg[0] == '~' && ft_strlen(arg) > 1)
		return (ft_strjoin(home, arg + 1));
	else
		return (ft_strdup(arg));
}

void	save_current_dir(void)
{
	t_dict	*kvp;
	char	*cwd;
	char	*tmp;

	kvp = get_kvp(g_meta.env, "PWD");
	cwd = getcwd(NULL, 0);
	if ((!kvp || !kvp->value) && !cwd)
	{
		tmp = g_meta.save_pwd;
		g_meta.save_pwd = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = g_meta.save_pwd;
		g_meta.save_pwd = ft_strjoin(tmp, "..");
		free(tmp);
		
	}
	else if (cwd)
		g_meta.save_pwd = getcwd(NULL, 0);
	else
		g_meta.save_pwd = ft_strdup(kvp->value);
	free(cwd);
}

void	ft_cd(char **args)
{
	char	*dir;
	char	*cwd;

	g_meta.status = 0;
	if (args[1] && !args[1][0])
		return ;
	dir = next_dir(args[1]);
	if (!dir)
		return ;
	cwd = getcwd(NULL, 0);
	update_old_pwd(cwd);
	free(cwd);
	if (chdir(dir) == 0)
	{
		cwd = getcwd(NULL, 0);
		update_pwd(dir, cwd);
		free(cwd);
		save_current_dir();
	}
	else
	{
		g_meta.status = BUILTIN_FAIL;
		perror("Minishell: cd");
	}
	free(dir);
}

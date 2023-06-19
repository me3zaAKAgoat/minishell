/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:27:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/19 02:32:36 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_wd(char *key)
{
	t_dict	*kvp;

	kvp = get_kvp(g_meta.env, key);
	free(kvp->value);
	kvp->value = getcwd(NULL, 0);
}

void	cd(char **args)
{
	update_env_wd("OLDPWD");
	chdir(args[1]);
	update_env_wd("PWD");
}

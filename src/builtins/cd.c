/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 02:27:11 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 08:52:38 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *old_pwd)
{
	char	*pwd;
	t_node	*iterator_old_pwd;
	t_node	*iterator_pwd;
	t_dict	*kvp_pwd;
	t_dict	*kvp_old_pwd;

	iterator_pwd = g_meta.env;
	while (iterator_pwd)
	{
		kvp_pwd = iterator_pwd->content;
		if (!ft_strcmp(kvp_pwd->key, "PWD"))
		{
			iterator_old_pwd = g_meta.env;
			while (iterator_old_pwd)
			{
				kvp_old_pwd = iterator_old_pwd->content;
				if (!ft_strcmp(kvp_old_pwd->key, "OLDPWD"))
				{
					kvp_old_pwd->value = old_pwd;
					pwd = getcwd(NULL, 0);
					if (!pwd)
					{
						printf("getcwd error\n");
						exit(1);
					}
					kvp_pwd->value = pwd;
					return ;
				}
				iterator_old_pwd = iterator_old_pwd->next;
			}
		}
		iterator_pwd = iterator_pwd->next;
	}
}

void	cd(char **args)
{
	char	*old_pwd;
	// return of getcwd func should freed
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		printf("getcwd error\n");
		exit(1);
	}
	chdir(args[1]);
	update_pwd(old_pwd);
	// handle removal of directories when deeply nested inside of a child
}

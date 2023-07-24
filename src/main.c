/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:29:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/24 16:50:39 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	g_meta;

void	init_flags(void)
{
	g_meta.flags.set_old_pwd = 0;
	g_meta.flags.expansion_heredoc = 1;
}

int	main(int ac, char **av, char **env)
{
	(void)ac, (void)av;
	if (*env == NULL)
		g_meta.env = init_env_manually();
	else
		g_meta.env = init_env(env);
	g_meta.status = 0;
	init_flags();
	g_meta.pids = NULL;
	prompt_loop();
}

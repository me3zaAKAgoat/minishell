/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:29:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/22 21:54:07 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	g_meta;

int	main(int ac, char **av, char **env)
{
	(void)ac, (void)av;
	if (*env == NULL)
		g_meta.env = init_env_manually();
	else
		g_meta.env = init_env(env);
	g_meta.set_old_pwd = 0;
	g_meta.status = 0;
	g_meta.flags.flag_expansion_heredoc = 1;
	g_meta.pids = NULL;
	prompt_loop();
}

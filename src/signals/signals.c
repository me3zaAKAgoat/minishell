/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 23:56:41 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 12:23:18 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(void)
{
	if (ll_size(g_meta.pids))
	{
		while (ll_size(g_meta.pids))
		{
			kill((*(pid_t *)g_meta.pids->content), SIGKILL);
			ll_del_one(ll_shift(&g_meta.pids), free);
		}
		write(1, "\n", 1);
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_meta.status = 130;
}

void	redirect_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (__sighandler_t)handle_sigint);
}

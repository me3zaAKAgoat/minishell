/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 23:56:41 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 02:50:21 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(void)
{
	if (!ll_size(g_meta.pids))
	{
		write(1, "\n", 1);
		g_meta.status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	prompt_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (__sighandler_t)handle_sigint);
}

void	execution_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

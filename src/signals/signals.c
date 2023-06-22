/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 23:56:41 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/22 22:01:43 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(void)
{
	t_node *iterator;

	iterator = g_meta.pids;
	if (ll_size(iterator))
	{
		while (iterator)
		{
			kill((*(pid_t *)iterator->content), SIGINT);
			iterator = iterator->next;
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

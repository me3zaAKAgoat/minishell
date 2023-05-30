/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:29:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/30 10:29:47 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	init_meta(t_meta *meta, char **env)
{
	meta->env = init_env(env);
}

int main(int ac, char **av, char **env)
{
	char	*input;
	t_meta	meta;
	t_dict	*kvp;

	(void)ac;
	(void)av;
	init_meta(&meta, env);
	while (1)
	{
		input = readline("\033[1;33m$\033[0m\033[1;35m-minishell > \033[0m");
		printf("%s\n", input);
	}
}
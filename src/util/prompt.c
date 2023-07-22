/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:35:48 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/22 20:41:06 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*relative_wd(void)
{
	char	*wd;
	t_dict	*kvp;
	char	*relative_path;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		kvp = get_kvp(g_meta.env, "PWD");
		if (kvp && kvp->value)
			relative_path = kvp->value;
		else
			relative_path = "removed directory";
	}
	else
		relative_path = wd;
	while (*relative_path)
	{
		if (!ft_strchr(relative_path, '/'))
			break ;
		relative_path++;
	}
	relative_path = ft_strdup(relative_path);
	free(wd);
	return (relative_path);
}

char	*prompt_string(void)
{
	char	*relative_path;
	char	*prompt;
	char	*words[10];

	relative_path = relative_wd();
	if (g_meta.status)
		words[0] = RED;
	else
		words[0] = GREEN;
	words[1] = "$ ";
	words[2] = COLOR_OFF;
	words[3] = PURPLE;
	words[4] = relative_path;
	words[5] = COLOR_OFF;
	if (g_meta.status)
		words[6] = RED;
	else
		words[6] = GREEN;
	words[7] = " ► ";
	words[8] = COLOR_OFF;
	words[9] = NULL;
	prompt = join_arr(words, "");
	free(relative_path);
	return (prompt);
}

void	prompt_loop(void)
{
	char	*cmd_line;
	char	*prompt;

	prompt_signals();
	while (1)
	{
		prompt = prompt_string();
		cmd_line = readline(prompt);
		free(prompt);
		add_history(cmd_line);
		parse(cmd_line);
		free(cmd_line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:35:48 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/19 20:19:55 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*relative_wd(void)
{
	char	*wd;
	char	*relative_path;

	wd = getcwd(NULL, 0);
	if (!wd)
		return (NULL);
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
	words[0] = YELLOW;
	words[1] = "$- ";
	words[2] = COLOR_OFF;
	words[3] = PURPLE;
	if (relative_path)
		words[4] = relative_path;
	else
		words[4] = "(nil)";
	words[5] = COLOR_OFF;
	words[6] = YELLOW;
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

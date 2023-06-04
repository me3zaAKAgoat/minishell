/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:35:48 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/04 02:35:37 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*relative_wd(void)
{
	char	*wd;
	char	*relative_path;

	wd = getcwd(NULL, 0);
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
	words[4] = relative_path;
	words[5] = COLOR_OFF;
	words[6] = YELLOW;
	words[7] = " ► ";
	words[8] = COLOR_OFF;
	words[9] = NULL;
	prompt = array_to_str(words, "");
	free(relative_path);
	return (prompt);
}

void	prompt_loop(t_meta *meta)
{
	char	*cmd_line;
	char	*prompt;

	while (1)
	{
		prompt = prompt_string();
		cmd_line = readline(prompt);
		free(prompt);
		parse(meta, cmd_line);
		free(cmd_line);
	}
}

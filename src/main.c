/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:29:54 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/02 02:41:34 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_meta *meta, char **env)
{
	install_signals();
	meta->env = init_env(env);
}

char	*relative_wd(void)
{
	char	*wd;
	char	*relative_path;

	wd = getcwd(NULL, 0);
	relative_path = wd;
	while (*relative_path)
	{
		if (!ft_strchr(relative_path, '/'))
			break;
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

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*prompt;
	t_meta	meta;

	(void)ac, (void)av;
	init(&meta, env);
	while (1)
	{
		prompt = prompt_string();
		input = readline(prompt);
		free(prompt);
		if (!input)
			exit(0); // this should be status of last executed command instead of 0
		printf("%s\n", input);
		free(input);
	}
}

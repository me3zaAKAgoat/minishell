/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:10:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/03 02:46:41 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_meta *meta, char *raw_input)
{
	// char	**arr;
	char	*input;

	if (!raw_input)
		exit(0); // this should be status of last executed command instead of 0
	input = strip(raw_input);
	// if (input[ft_strlen(input) - 1] == '|')
	// 	// open heredoc
	// arr = ft_split(input, '|');
	// while (arr)
	// 	parse_simple_cmd()
	if (!ft_strncmp(input, "heredoc", ft_strlen(input)) && ft_strlen(input))
	{
		char	*heredoc = here_doc("END");
		if (heredoc)
			printf("%s\n", heredoc);
		free(heredoc);
	}
	if (!ft_strncmp(input, "env", ft_strlen(input)) && ft_strlen(input))
		print_env(meta);
	free(input);
}

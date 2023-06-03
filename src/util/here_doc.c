/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:48:13 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/02 22:10:54 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_heredoc(void)
{
	write(1, "heredoc>", ft_strlen("heredoc>"));
	return (get_next_line(0));
}

char	*here_doc(char *eof)
{
	char	*read_buf;
	char	*return_buf;
	char	*tmp;

	return_buf = NULL;
	read_buf = prompt_heredoc();
	while (read_buf)
	{
		if (!ft_strncmp(read_buf, eof, ft_strlen(read_buf) - 1))
			return (free(read_buf), return_buf);
		if (!return_buf)
			return_buf = ft_strdup(read_buf);
		else
		{
			tmp = ft_strjoin(return_buf, read_buf);
			free(return_buf);
			return_buf = tmp;
		}
		free(read_buf);
		read_buf = prompt_heredoc();
	}
	return (return_buf);
}

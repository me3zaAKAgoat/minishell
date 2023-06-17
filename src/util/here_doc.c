/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:48:13 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 00:08:39 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt_heredoc(void)
{
	write(1, "heredoc>", ft_strlen("heredoc>"));
	return (get_next_line(0));
}

static char	*unique_tmp_name(void)
{
	int		i;
	char	*unique_name;
	char	*identifier;

	i = 0;
	while (i < INT_MAX)
	{
		identifier = ft_itoa(i);
		unique_name = ft_strjoin("/tmp/heredoctmp", identifier);
		if (!access(unique_name, F_OK))
			return (free(identifier), unique_name);
		free(identifier);
		free(unique_name);
		i++;
	}
	return (NULL);
}

int	here_doc(char *eof)
{
	char	*read_buf;
	int		fd;

	fd = open(unique_tmp_name(), O_RDWR | O_CREAT);
	if (fd == -1)
		return (-1);
	read_buf = prompt_heredoc();
	while (read_buf)
	{
		if (!ft_strncmp(read_buf, eof, ft_strlen(read_buf) - 1))
			return (free(read_buf), fd);
		else
			write(fd, read_buf, ft_strlen(read_buf));
		free(read_buf);
		read_buf = prompt_heredoc();
	}
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:48:13 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/29 17:07:12 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt_heredoc(void)
{
	write(1, "> ", ft_strlen("> "));
	return (get_next_line(0));
}

static char	*unique_tmp_name(void)
{
	int		i;
	char	*unique_filename;
	char	*identifier;

	i = 0;
	while (i < INT_MAX)
	{
		identifier = ft_itoa(i);
		unique_filename = ft_strjoin("/tmp/heredoctmp", identifier);
		if (access(unique_filename, F_OK) != 0)
			return (free(identifier), unique_filename);
		free(identifier);
		free(unique_filename);
		i++;
	}
	return (NULL);
}

void	process_heredoc_line(char *read_buf, int fd)
{
	char	*tmp;

	if (ft_strchr(read_buf, '$') && g_meta.flags.expansion_heredoc == 1)
	{
		tmp = read_buf;
		read_buf = expanded_string(tmp);
		free(tmp);
		write(fd, read_buf, ft_strlen(read_buf));
	}
	else
		write(fd, read_buf, ft_strlen(read_buf));
	free(read_buf);
}

void heredoc_loop(char *eof, int fd)
{
	char	*read_buf;
	char	*no_nl_buf;

	read_buf = prompt_heredoc();
	while (read_buf)
	{
		if (g_meta.heredoc_fd == -1)
		{
			free(read_buf);
			break ;
		}
		no_nl_buf = ft_substr(read_buf, 0, ft_strlen(read_buf) - 1);
		if (!ft_strcmp(no_nl_buf, eof))
		{
			free(no_nl_buf);
			free(read_buf);
			break ;
		}
		process_heredoc_line(read_buf, fd);
		read_buf = prompt_heredoc();
		free(no_nl_buf);
	}
}

/*
close the unique filename and remove it
break the heredoc loop
re prompt
*/
char	*here_doc(char *eof)
{
	char	*unique_filename;
	int		fd;

	unique_filename = unique_tmp_name();
	fd = open(unique_filename, O_RDWR | O_CREAT, 0644);
	g_meta.heredoc_fd = fd;
	if (fd == -1)
		return (free(eof), NULL);
	heredoc_loop(eof, fd);
	(close(fd), free(eof));
	g_meta.heredoc_fd = -1;
	return (unique_filename);
}

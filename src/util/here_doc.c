/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:48:13 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 20:50:41 by echoukri         ###   ########.fr       */
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

static void	handle_sigint(int i)
{
	(void)i;
	exit(EXIT_FAILURE);
}

char	*here_doc(char *eof)
{
	char	*read_buf;
	char	*tmp;
	char	*eof_check;
	char	*unique_filename;
	int		fd;

	signal(SIGINT, handle_sigint);
	unique_filename = unique_tmp_name();
	fd = open(unique_filename, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		return (free(eof), NULL);
	read_buf = prompt_heredoc();
	while (read_buf)
	{
		eof_check = ft_substr(read_buf, 0, ft_strlen(read_buf) - 1);
		if (!ft_strcmp(eof_check, eof))
			return (free(read_buf), free(eof),
				free(eof_check), unique_filename);
		if (ft_strchr(read_buf, '$') && g_meta.flags.flag_expansion_heredoc == 1)
		{
			tmp = read_buf;
			read_buf = expanded_string(tmp);
			free(tmp);
			write(fd, read_buf, ft_strlen(read_buf));
		}
		else
			write(fd, read_buf, ft_strlen(read_buf));
		free(read_buf);
		free(eof_check);
		read_buf = prompt_heredoc();
	}
	close(fd);
	free(eof);
	return (unique_filename);
}

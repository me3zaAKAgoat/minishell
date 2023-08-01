/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 02:38:45 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/29 20:10:05 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_command_args(t_node *token, t_command *cmd)
{
	char	**tmp;
	size_t	arr_len;

	if (cmd->args)
		arr_len = strarr_len(cmd->args);
	else
		arr_len = 0;
	tmp = malloc((arr_len + 2) * sizeof(char *));
	ft_memcpy(tmp, cmd->args, arr_len * sizeof(char *));
	tmp[arr_len] = ft_strdup(((t_token *)token->content)->value);
	tmp[arr_len + 1] = NULL;
	free(cmd->args);
	cmd->args = tmp;
}

int	open_heredoc(char *delim)
{
	char	*heredoc_filename;
	char	*old_delim;
	int		fd;

	old_delim = delim;
	delim = unexpand_heredoc_delimiter(delim);
	if (!delim)
		delim = ft_strdup(old_delim);
	heredoc_filename = here_doc(delim);
	if (!heredoc_filename)
		fd = -1;
	else
	{
		fd = open(heredoc_filename, O_RDONLY);
		unlink(heredoc_filename);
		free(heredoc_filename);
	}
	return (fd);
}

void	input_redirections(t_node *tokens, t_command *cmd)
{
	if (((t_token *)tokens->content)->type == IN && !cmd->io_error)
	{
		tokens = tokens->next;
		if (cmd->infile >= 0)
			close(cmd->infile);
		cmd->infile = open(((t_token *)tokens->content)->value, O_RDONLY);
		if (cmd->infile == -1)
			(werror("Minishell: "),
				werror(((t_token *)tokens->content)->value),
				perror(" "), cmd->io_error = 1);
	}
	else if (((t_token *)tokens->content)->type == HEREDOC && !cmd->io_error)
	{
		tokens = tokens->next;
		if (cmd->infile >= 0)
			close(cmd->infile);
		cmd->infile = open_heredoc(((t_token *)tokens->content)->value);
		if (cmd->infile == -1)
			(werror("Minishell: "),
				werror(((t_token *)tokens->content)->value),
				perror(" "), cmd->io_error = 1);
	}
}

void	output_redirections(t_node *tokens, t_command *cmd)
{
	if (((t_token *)tokens->content)->type == OUT && !cmd->io_error)
	{
		tokens = tokens->next;
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		cmd->outfile = open(((t_token *)tokens->content)->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->outfile == -1)
			(werror("Minishell: "),
				werror(((t_token *)tokens->content)->value),
				perror(" "), cmd->io_error = 1);
	}
	else if (((t_token *)tokens->content)->type == APPEND && !cmd->io_error)
	{
		tokens = tokens->next;
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		cmd->outfile = open(((t_token *)tokens->content)->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->outfile == -1)
			(werror("Minishell: "),
				werror(((t_token *)tokens->content)->value),
				perror(" "), cmd->io_error = 1);
	}
}

t_command	*create_command(t_node *tokens)
{
	t_command	*cmd;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	while (((t_token *)tokens->content)->type != PIPE
		&& ((t_token *)tokens->content)->type != END && !g_meta.halt_parsing)
	{
		if (IN <= ((t_token *)tokens->content)->type
			&& ((t_token *)tokens->content)->type <= APPEND)
		{
			input_redirections(tokens, cmd);
			output_redirections(tokens, cmd);
			tokens = tokens->next->next;
		}
		while (((t_token *)tokens->content)->type != END
			&& STRING <= (((t_token *)tokens->content)->type)
			&& (((t_token *)tokens->content)->type <= SQUOTE))
		{
			join_command_args(tokens, cmd);
			tokens = tokens->next;
		}
	}
	return (cmd);
}

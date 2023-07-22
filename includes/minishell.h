/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:30:04 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/22 18:26:41 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "linked_list.h"
# include "libft.h"
# include "get_next_line.h"

/* MACROS */
# define READ_END 0
# define MAX_SHLVL 1000
# define WRITE_END 1
# define CMD_FAIL 126
# define CMD_UNKNOWN 127
# define CMD_INT 130
# define BUILTIN_INCORRECT_USAGE 2
# define BUILTIN_FAIL 1

# define COLOR_OFF "\033[0m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

/* TYPES */
typedef struct s_dict {
	char	*key;
	char	*value;
}	t_dict;

typedef struct s_flags {
	int	expansion_heredoc;
	int	set_old_pwd;
}	t_flags;

typedef struct s_meta {
	t_node	*env;
	int		status;
	t_flags	flags;
	t_node	*pids;
}	t_meta;

typedef struct s_command {
	char	**args;
	int		infile;
	int		outfile;
	int		io_error;
}	t_command;

typedef enum e_token_type {
	IN,
	OUT,
	HEREDOC,
	APPEND,
	STRING,
	DQUOTE,
	SQUOTE,
	SPACEE,
	PIPE,
	ERR,
	END,
}	t_token_type;

typedef struct s_token {
	char			*value;
	t_token_type	type;
}	t_token;

/* DECLARATIONS */
extern	void		clear_kvp(t_dict *kvp);
extern	t_dict	*new_kvp(char *key, char *val);
extern	t_dict	*get_kvp(t_node *kvp_list, char *key);
extern	t_node	*init_env_manually(void);
extern	t_node	*init_env(char **env);
extern	void		shlvl_too_high(int new_shlvl, t_dict **kvp);
extern	void		handle_shlvl_limit(int new_shlvl, t_dict **kvp);
extern	void		update_shlvl(t_node *head);
extern	void		ft_cd(char **args);
extern	void		ft_echo(char **args);
extern	void		ft_env(char **args);
extern	void		ft_exit(char **args);
extern	void		ft_export(char **args);
extern	int		key_is_valid(char *key);
extern	char		*get_key(char *arg);
extern	char		*get_value(char *arg);
extern	void		ft_pwd(void);
extern	void		ft_unset(char **args);
extern	void		handle_builtin(t_command *cmd);
extern	int		is_builtin(t_command *cmd);
extern	void		prompt_signals(void);
extern	void		execution_signals(void);
extern	char		*join_arr(char **words, char *sep);
extern	void		prompt_loop(void);
extern	void		parse(char *cmd_line);
extern	char		*here_doc(char *eof);
extern	int		ft_isspace(char c);
extern	t_node	*tokenize(char *cmd_line);
extern	void		remove_space_tokens(t_node **head);
extern	void		clear_token(t_token *token);
extern	t_token	*new_token(char *value, t_token_type type);
extern	char		**envp_generator(t_node *env);
extern	void		free_envp(char **envp);
extern	t_command	*init_command(void);
extern	void		clear_command(t_command *cmd);
extern	void		join_command_args(t_node *tokens, t_command *cmd);
extern	t_command	*create_command(t_node *tokens);
extern	char		*unexpand_heredoc_delimiter(char *delim);
extern	void		execute_commands(t_node *cmds);
extern	void		setup_pipes(int first_pipe[2], int second_pipe[2]);
extern	void		close_pipes(int first_pipe[2], int second_pipe[2]);
extern	void		cmd_wrapper(t_command *cmd,
						int first_pipe[2], int second_pipe[2]);
extern	void		pipeline(t_node *cmds);
extern	void		input_redirection(t_command *cmd);
extern	void		out_redirection(t_command *cmd);
extern	char		**get_pathenv(char	*envp[]);
extern	char		*get_cmdpath(char	**paths, char	*cmd);
extern	void		handle_bin_cmd(char **args, char **envp);
extern	int		ft_strcmp(const char *s1, const char *s2);
extern	t_dict	*get_kvp(t_node *kvp_list, char *key);
extern	void		werror(char *msg);
extern	char		*lex_quotes(char *cmd_line, char delim);
extern	char		*lex_string(char *cmd_line);
extern	int		lexical_errors(t_node	*tokens);
extern	void		print_syntax_error(char *value);
extern	int		syntax_error_pipe(t_token *current, t_node *iterator, int i);
extern	int		syntax_error_redirection(t_node *iterator, t_token *current);
extern	int		is_number(char *str);
extern	long long	ft_atoll(const char *str);
extern	void		expand_envs(t_node *tokens);
extern	char		*expanded_string(char *initial_str);
extern	char		*append(char *initial_str, char *str, int *i, int *j);
extern	char		*append_to_result(char *str, char *substring);
extern	int		count_key_length(char *key, int i);
extern	void		is_delimiter_inside_quotes(t_node *tokens);
extern	char		*remove_last_quote(char *str);
extern	size_t	strarr_len(char **arr);

extern t_meta	g_meta;

#endif
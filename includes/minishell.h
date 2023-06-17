/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:30:04 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 09:26:31 by echoukri         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "linked_list.h"
# include "libft.h"
# include "get_next_line.h"

/* MACROS */
# define READ_END 0
# define WRITE_END 1
# define CMD_FAIL 126
# define CMD_UNKNOWN 126

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

typedef struct s_meta {
	t_node	*env;
	int		status;
	t_node	*pids;
}	t_meta;

typedef struct s_command {
	char	*args;
	char	*infile;
	char	*truncfile;
	char	*delim;
	char	*appendfile;
}	t_command;

typedef enum e_token_type {
	IN,
	OUT,
	HEREDOC,
	APPEND,
	STRING,
	PIPE,
	END
}	t_token_type;

typedef struct s_token {
	char			*value;
	t_token_type	type;
}	t_token;

/* DECLARATIONS */
extern	void		clear_kvp(t_dict *kvp);
extern	t_dict	*new_kvp(char *key, char *val);
extern	t_node	*init_env(char **env);
extern	void		cd(char **args);
extern	void		print_env(char **args);
extern	void		shell_exit(char **args);
extern	void		export(char **args);
extern	void		pwd(char **args);
extern	void		unset(char **args);
extern	int		handle_redirectable_builtin(char **args);
extern	int		handle_non_redirectable_builtin(char **args);
extern	void		redirect_signals(void);
extern	char		*join_arr(char **words, char *sep);
extern	void		prompt_loop(void);
extern	void		parse(char *cmd_line);
extern	char		*strip(char *str);
extern	char		*here_doc(char *eof);
extern	char		*expand_env(t_node *env, char *key);
extern	int		ft_isspace(char c);
extern	t_node	*tokenize(char *cmd_line);
extern	void		clear_token(t_token *token);
extern	t_token	*new_token(char *value, t_token_type type);
extern	char		**envp_generator(t_node *env);
extern	void		free_envp(char **envp);
extern	t_command	*init_command(void);
extern	void		clear_command(t_command *cmd);
extern	void		join_command_args(t_node *tokens, t_command *cmd);
extern	t_command	*create_command(t_node *tokens);
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

extern t_meta	g_meta;

#endif
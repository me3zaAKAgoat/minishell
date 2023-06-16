/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:30:04 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/16 03:08:42 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "linked_list.h"
# include "libft.h"
# include "get_next_line.h"

	/* MACROS */
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
extern	void		unset(t_meta *meta, char *key);
extern	void		pwd(void);
extern	void		export(t_meta *meta, char *key, char *value);
extern	void		print_env(t_meta *meta);
extern	void		cd(t_meta *meta, const char *path);
extern	void		redirect_signals(void);
extern	char		*join_arr(char **words, char *sep);
extern	void		prompt_loop(t_meta *meta);
extern	void		parse(t_meta *meta, char *cmd_line);
extern	char		*strip(char *str);
extern	char		*here_doc(char *eof);
extern	void		shell_exit(t_meta *meta);
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
extern	void		setup_redirections(t_node *tokens, t_command *cmd);
extern	t_command	*create_command(t_node *tokens);

#endif
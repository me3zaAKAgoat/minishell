/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:30:04 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/02 22:08:33 by echoukri         ###   ########.fr       */
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
# include "types.h"

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

/* DECLARATIONS */
extern	void		clear_kvp(t_dict *kvp);
extern	t_dict	*new_kvp(char *key, char *val);
extern	t_node	*init_env(char **env);
extern	void		unset(t_meta *meta, char *key);
extern	void		pwd(void);
extern	void		export(t_meta *meta, char *key, char *value);
extern	void		print_env(t_meta *meta);
extern	void		cd(t_meta *meta, const char *path);
extern	void		install_signals(void);
extern	char		*array_to_str(char **words, char *sep);
extern	void		prompt_loop(t_meta *meta);
extern	void		parse(t_meta *meta, char *input);
extern	char		*strip(char *str);
extern	char		*here_doc(char *eof);
extern	void		shell_exit(t_meta *meta);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:30:04 by echoukri          #+#    #+#             */
/*   Updated: 2023/05/31 14:22:56 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "linked_list.h"
# include "libft.h"

/* MACROS */
# define CMD_FAIL 126
# define CMD_UNKNOWN 126

/* TYPES */
typedef struct s_dict {
	char	*key;
	char	*value;
}	t_dict;

typedef struct s_meta {
	t_node	*env;
	char	*cwd;
	int		outfile;
	int		infile;
}	t_meta;
/*cwd stand for current working directory*/

/* DECLARATIONS */

extern	void		clear_kvp(t_dict *kvp);
extern	t_dict	*new_kvp(char *key, char *val);
extern	t_node	*init_env(char **env);
extern	void		unset(t_meta *meta, char *key);
extern	void		pwd(t_meta *meta);
extern	void		export(t_meta *meta, char *key, char *value);
extern	void		print_env(t_meta *meta);

#endif
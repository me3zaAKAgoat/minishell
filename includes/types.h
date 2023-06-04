/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:10:40 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/04 03:16:02 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

/* TYPES */
typedef struct s_dict {
	char	*key;
	char	*value;
}	t_dict;

typedef struct s_meta {
	t_node	*env;
	int		status;
}	t_meta;

typedef enum e_token_type {
	STRING,
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	ENV,
	END
}	t_token_type;

typedef struct s_token {
	char			*value;
	t_token_type	type;
}	t_token;

#endif
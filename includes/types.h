/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:10:40 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/03 03:50:19 by echoukri         ###   ########.fr       */
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

#endif
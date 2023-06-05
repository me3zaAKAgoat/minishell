/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:10:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/05 02:18:01 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_meta *meta, char *cmd_line)
{
	t_node	*tokens;

	(void)meta;
	if (!cmd_line)
		exit(0); // this should be status of last executed command instead of 0
	tokens = tokenize(cmd_line);
	if (!tokens)
		return ;
	ll_clear(&tokens, clear_token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:10:00 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/02 05:37:55 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_meta *meta, char *input)
{
	if (!input)
		exit(0); // this should be status of last executed command instead of 0
	if (!ft_strncmp(input, "env", ft_strlen(input)) && ft_strlen(input))
		print_env(meta);
}

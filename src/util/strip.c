/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:49:10 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/04 02:55:47 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == 32 || c == 9 || c == 10 || c == 13 || c == 12 || c == 11);
}

char	*strip(char *str)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && ft_isspace(str[start]))
		start++;
	while (end > 0 && ft_isspace(str[end]))
		end--;
	return (ft_substr(str, start, end - start + 1));
}

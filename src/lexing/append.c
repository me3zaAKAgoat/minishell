/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:53:11 by ekenane           #+#    #+#             */
/*   Updated: 2023/07/21 14:54:10 by ekenane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_dollar(int *j, int *i, char *str)
{
	str = append_to_result(str, ft_strdup("$"));
	(*i) += 1;
	(*j) = (*i);
	return (str);
}

char	*append_normal_text(int *j, int *i, char *initial_str, char *str)
{
	(*j) = (*i);
	if (i == 0 && initial_str[(*i)] == '"')
		(*j) += 1;
	while (initial_str[(*i)] && initial_str[(*i)] != '$')
		(*i)++;
	str = append_to_result(str, ft_substr(initial_str, (*j), (*i) - (*j)));
	return (str);
}

char	*append(char *initial_str, char *str, int *i, int *j)
{
	if (initial_str[(*i)] == '$')
		str = append_dollar(j, i, str);
	else
		str = append_normal_text(j, i, initial_str, str);
	return (str);
}

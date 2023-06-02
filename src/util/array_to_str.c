/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:23:19 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/02 02:06:52 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*array_to_str(char **words, char *sep)
{
	int		i;
	int		result_size;
	char	*result;
	char	*builder;

	i = 0;
	result_size = 0;
	while (words[i])
		result_size += ft_strlen(words[i++]);
	result_size += (i - 1) * ft_strlen(sep) + 1;
	result = malloc(result_size * sizeof(char));
	if (!result)
		return (NULL);
	builder = result;
	i = 0;
	while (words[i])
	{
		if (i > 0)
			builder += ft_strlcpy(builder, sep, result_size);
		builder += ft_strlcpy(builder, words[i], result_size);
		i++;
	}
	*builder = 0;
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:23:19 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/03 04:49:23 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	result_size(char **words, char *sep)
{
	int		i;
	size_t	result_size;

	i = 0;
	result_size = 0;
	while (words[i])
		result_size += ft_strlen(words[i++]);
	result_size += (i - 1) * ft_strlen(sep) + 1;
	return (result_size);
}

static char	*joined_string(char *result, char **words, char *sep, size_t result_size)
{
	int		i;
	char	*builder;

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

char	*array_to_str(char **words, char *sep)
{
	char	*result;
	size_t	size;

	if (!words || !sep)
		return (NULL);
	size = result_size(words, sep);
	result = malloc(size * sizeof(char));
	if (!result)
		return (NULL);
	return (joined_string(result, words, sep, size));
}

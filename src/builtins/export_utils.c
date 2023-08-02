/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:29:32 by ekenane           #+#    #+#             */
/*   Updated: 2023/08/02 17:01:12 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_is_valid(char *key)
{
	int	i;
	int	len;

	if (!key)
		return (0);
	i = 0;
	len = ft_strlen(key) - 1;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (i < len)
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
			return (0);
		i++;
	}
	if (!ft_isalpha(key[len]) && key[len] != '_' && !ft_isdigit(key[len])
		&& key[len] != '+')
		return (0);
	if (key[len] == '+')
		return (2);
	return (1);
}

char	*get_key(char *arg)
{
	int		len;
	int		i;
	char	*key;

	len = 0;
	if (ft_strchr(arg, '+') && !ft_strchr(arg, '='))
		return (NULL);
	while (arg[len] && arg[len] != '=')
		len++;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (i < len)
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *arg)
{
	char	*value;
	int		len;
	int		i;
	char	*tmp;

	tmp = ft_strchr(arg, '=');
	if (!tmp)
		return (NULL);
	len = ft_strlen(tmp + 1);
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (i < len)
	{
		value[i] = tmp[i + 1];
		i++;
	}
	value[i] = '\0';
	return (value);
}

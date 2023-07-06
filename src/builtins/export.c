/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:31 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/23 18:31:02 by echoukri         ###   ########.fr       */
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

void	print_export(void)
{
	t_node	*iterator;
	t_dict	*kvp;

	iterator = g_meta.env;
	while (iterator)
	{
		kvp = iterator->content;
		write(1, "declare -x ", ft_strlen("declare -x "));
		write(1, kvp->key, ft_strlen(kvp->key));
		if (kvp->value)
		{
			write(1, "=\"", ft_strlen("=\""));
			write(1, kvp->value, ft_strlen(kvp->value));
			write(1, "\"", ft_strlen("\""));
		}
		write(1, "\n", ft_strlen("\n"));
		iterator = iterator->next;
	}
}

char	*get_key(char *arg)
{
	int		len;
	int		i;
	char	*key;

	len = 0;
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
	if (!value)
		return (NULL);
	return (value);
}

void	concatenate_values(t_dict *existing_pair, char *new_value)
{
	char	*concatenate_value;

	concatenate_value = ft_strjoin(existing_pair->value, new_value);
	free(existing_pair->value);
	existing_pair->value = concatenate_value;
}

void	modify_environment(char *key, char *value, int check)
{
	char	*tmp;
	t_dict	*exist_pair;

	tmp = key;
	key = ft_strtrim(tmp, "+");
	free(tmp);
	exist_pair = get_kvp(g_meta.env, key);
	if (check == 2)
	{
		if (exist_pair)
			concatenate_values(exist_pair, value);
		else
			ll_push(&g_meta.env, ll_new(new_kvp(key, value)));
	}
	else
	{
		if (exist_pair)
			(free(exist_pair->value), exist_pair->value = ft_strdup(value));
		else
			ll_push(&g_meta.env, ll_new(new_kvp(key, value)));
	}
	free(value);
	free(key);
}

int	update_env(char *arg)
{
	char	*key;
	char	*value;
	int		check;

	key = get_key(arg);
	value = get_value(arg);
	if (value && value[0] == '\0')
	{
		free(value);
		value = NULL;
	}
	if (!value)
		value = ft_strdup("");
	check = key_is_valid(key);
	if (!check)
		return (werror("Minishell: export: `"), werror(arg),
			free(value), free(key),
			werror("': not a valid identifier\n"),
			g_meta.status = BUILTIN_FAIL, -1);
	modify_environment(key, value, check);
	return (0);
}

void	ft_export(char **args)
{
	int	i;

	if (!args[1])
		return (print_export());
	i = 1;
	while (args[i])
	{
		if (update_env(args[i]) != -1)
			g_meta.status = 0;
		i++;
	}
}

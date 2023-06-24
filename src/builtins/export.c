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
	len = ft_strlen(key) - 1;
	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]) && key[len] != '+')
			return (0);
		i++;
	}
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

void	concatenate_values(t_dict *concatenate_pair, char *new_val)
{
	char	*concatenate_val;
	concatenate_val = ft_strjoin(concatenate_pair->value, new_val);
	free(concatenate_pair->value);
	concatenate_pair->value = ft_strdup(concatenate_val);
	free(concatenate_val);
}

char	*set_new_value(char **key_value_arr, char **args)
{
	char	*new_val;

	new_val = join_arr(key_value_arr + 1, "=");
	if (ft_strchr(args[1], '=') && !new_val)
		new_val = ft_strdup("");
	return (new_val);
}

void	replace_value(t_dict **existing_pair, char *new_val)
{
		free((*existing_pair)->value);
		(*existing_pair)->value = ft_strdup(new_val);
}

int	update_env(char **args)
{
	char	**key_value_arr;
	t_dict	*existing_pair;
	t_dict	*concatenate_pair;
	char	*new_val;
	char	*tmp_key;

	key_value_arr = ft_split(args[1], '=');
	if (!key_is_valid(key_value_arr[0]))
		return (werror("Minishell: export: `"), werror(args[1]),
			werror("': not a valid identifier\n"), split_clear(key_value_arr),
			g_meta.status = BUILTIN_FAIL, -1);
	new_val = set_new_value(key_value_arr, args);
	existing_pair = get_kvp(g_meta.env, key_value_arr[0]);
	tmp_key = ft_strtrim(key_value_arr[0], "+");
	concatenate_pair = get_kvp(g_meta.env, tmp_key);
	if (existing_pair)
		replace_value(&existing_pair, new_val);
	else if (concatenate_pair)
		concatenate_values(concatenate_pair, new_val);
	else
		ll_push(&g_meta.env, ll_new(new_kvp(tmp_key, new_val)));
	free(new_val);
	free(tmp_key);
	split_clear(key_value_arr);
	return (0);
}

void	ft_export(char **args)
{
	if (!args[1])
		return (print_export());
	if (update_env(args) != -1)
		g_meta.status = 0;
}

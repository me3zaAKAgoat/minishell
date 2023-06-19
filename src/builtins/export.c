/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:31 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/17 08:52:50 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_is_valid(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
			return (0);
		i++;
	}
	return (1);
}

void	update_value_of_key(t_node **env, char *key, char *new_value)
{
	t_dict	*kvp;
	t_node	*iterator;

	iterator = (*env);
	while (iterator)
	{
		kvp = iterator->content;
		if (!ft_strcmp(kvp->key, key))
		{
			free(kvp->value);
			kvp->value = new_value;
		}
		iterator = iterator->next;
	}
}

int	equal_is_exist(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == '=')
			return (1);
		i++;
	}
	return (0);
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
		write(1, "=\"", ft_strlen("=\""));
		write(1, kvp->value, ft_strlen(kvp->value));
		write(1, "\"", ft_strlen("\""));
		write(1, "\n", ft_strlen("\n"));
		iterator = iterator->next;
	}
}

void	export(char **args)
{
	t_dict	*tmp;
	char	*value;
	char	**arr;
	// export without arguments ==> print all env variables ex.(declare -x key="value")
	tmp = NULL;
	if (!args[1])
		return (print_export());
	arr = ft_split(args[1], '=');
	// key should be valid
	if (!key_is_valid(arr[0]))
	{
		write(2, "Minishell: export: `", ft_strlen("Minishell: export: `"));
		write(2, args[1], ft_strlen(args[1]));
		write(2, "': not a valid identifier\n",
			ft_strlen("': not a valid identifier\n"));
		split_clear(arr);
		return ;
	}
	// key without value (exprot key | export key=)
	else if (!arr[1])
	{
		// key without value & without equal '=' should added to the env but don't print it
		if (!equal_is_exist(args[1]))
			return ;
		value = ft_strdup("");
	}
	else
		value = join_arr(arr + 1, "");
	// key already exist ==> update the value
	if (get_kvp(g_meta.env, arr[0]))
		update_value_of_key(&g_meta.env, arr[0], value);
	// new key ==> create new kvp
	else
	{
		tmp = new_kvp(arr[0], value);
		free(value);
		if (!tmp)
			return ;
		ll_push(&g_meta.env, ll_new(tmp));
	}
	split_clear(arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:31 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/19 14:01:01 by echoukri         ###   ########.fr       */
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
			write(1, "\n", ft_strlen("\n"));
		}
		iterator = iterator->next;
	}
}

void	update_env(char **args)
{
	char	**key_value_arr;
	t_dict	*existing_pair;
	char	*joined_val;

	key_value_arr = ft_split(args[1], '=');
	if (!key_is_valid(key_value_arr[0]))
	{
		werror("Minishell: export: `");
		werror(args[1]);
		werror("': not a valid identifier\n");
		split_clear(key_value_arr);
		return ;
	}
	joined_val = join_arr(key_value_arr + 1, "=");
	existing_pair = get_kvp(g_meta.env, key_value_arr[0]);
	if (existing_pair)
	{
		free(existing_pair->value); 
		existing_pair->value = ft_strdup(joined_val); 
	}
	else
		ll_push(&g_meta.env, ll_new(new_kvp(key_value_arr[0], joined_val)));
	free(joined_val);
	split_clear(key_value_arr);
}

void	export(char **args)
{
	if (!args[1])
		return (print_export());
	update_env(args);
	exit(0);
}

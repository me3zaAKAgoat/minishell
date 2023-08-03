/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:38:56 by echoukri          #+#    #+#             */
/*   Updated: 2023/08/03 15:21:36 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_generator(t_node *env)
{
	char	**envp;
	char	**arr_iter;
	t_node	*ll_iter;
	t_dict	*kvp;
	char	*tmp[3];

	envp = malloc((sizeof(char *)) * (ll_size(env) + 1));
	if (!envp)
		return (NULL);
	arr_iter = envp;
	ll_iter = env;
	while (ll_iter)
	{
		kvp = ll_iter->content;
		tmp[0] = kvp->key;
		tmp[1] = kvp->value;
		tmp[2] = NULL;
		*arr_iter = join_arr(tmp, "=");
		ll_iter = ll_iter->next;
		arr_iter++;
	}
	*arr_iter = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	special_env_init(t_node *head)
{
	t_dict	*oldpwd_kvp;

	oldpwd_kvp = new_kvp("OLDPWD", NULL);
	if (oldpwd_kvp)
		ll_push(&head, ll_new(oldpwd_kvp));
	update_shlvl(head);
}

t_node	*init_env(char **env)
{
	t_node	*head;
	char	**arr;
	t_dict	*tmp_dict;
	char	*tmp_str;

	if (!env)
		return (NULL);
	head = NULL;
	while (*env)
	{
		arr = ft_split(*env, '=');
		tmp_str = join_arr(arr + 1, "=");
		if (!tmp_str)
			tmp_str = ft_strdup("");
		tmp_dict = new_kvp(arr[0], tmp_str);
		if (tmp_dict)
			ll_push(&head, ll_new(tmp_dict));
		free(tmp_str);
		split_clear(arr);
		env++;
	}
	special_env_init(head);
	return (head);
}

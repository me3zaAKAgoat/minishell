/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekenane <ekenane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:38:56 by echoukri          #+#    #+#             */
/*   Updated: 2023/07/21 14:36:01 by ekenane          ###   ########.fr       */
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
	update_shlvl(head);
	return (head);
}

t_node	*init_env_manually(void)
{
	t_node	*head;
	t_dict	*tmp_dict;

	head = NULL;
	tmp_dict = new_kvp("SHLVL", "1");
	if (tmp_dict)
		ll_push(&head, ll_new(tmp_dict));
	tmp_dict = new_kvp("_", "/usr/bin/env");
	if (tmp_dict)
		ll_push(&head, ll_new(tmp_dict));
	tmp_dict = new_kvp("PWD", getcwd(NULL, 0));
	if (tmp_dict)
		ll_push(&head, ll_new(tmp_dict));
	tmp_dict = new_kvp("PATH", "/goinfre/ekenane/.brew/bin:\
		/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:\
		/Library/Apple/usr/bin:/goinfre/ekenane/.brew/bin");
	if (tmp_dict)
		ll_push(&head, ll_new(tmp_dict));
	return (head);
}

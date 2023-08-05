/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:11:05 by echoukri          #+#    #+#             */
/*   Updated: 2023/08/05 22:50:47 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xddvoid(void)
{
	return ;
}

enum e_token_type	string_type(char **arr)
{
	if (strarr_len(arr) != 1)
		return (NON_JOINABLE_STR);
	return (STRING);
}

void	split_expand_value_helper(char **arr, t_node *tokens)
{
	int		i;
	t_token	*tmp_token;

	i = 1;
	while (arr[i])
	{
		tmp_token = new_token(ft_strdup(arr[i]), NON_JOINABLE_STR);
		if (!tmp_token)
			continue ;
		ll_push(&tokens, ll_new(tmp_token));
		i++;
	}
}

void	split_expand_value(t_node *tokens)
{
	char	**arr;
	int		i;
	t_node	*next_tmp;
	t_token	*token;
	t_token	*tmp_token;

	token = tokens->content;
	arr = ft_split(token->value, ' ');
	if (!arr)
		return ;
	clear_token(token);
	next_tmp = tokens->next;
	i = 0;
	tmp_token = new_token(ft_strdup(arr[i]), string_type(arr));
	if (!tmp_token)
		return (split_clear(arr), xddvoid());
	tokens->content = tmp_token;
	tokens->next = NULL;
	split_expand_value_helper(arr, tokens);
	split_clear(arr);
	ll_last(tokens)->next = next_tmp;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me3za <me3za@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:35:24 by ekenane           #+#    #+#             */
/*   Updated: 2023/08/06 13:48:06 by me3za            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_too_high(int new_shlvl, t_dict **kvp)
{
	char	*tmp;

	werror("Minishell : warning: shell level (");
	tmp = ft_itoa(new_shlvl);
	werror(tmp);
	free(tmp);
	werror(") too high, resetting to 1\n");
	(*kvp)->value = ft_itoa(1);
}

void	handle_shlvl_limit(int new_shlvl, t_dict **kvp)
{
	if (new_shlvl == MAX_SHLVL)
		(*kvp)->value = ft_strdup("");
	else if (new_shlvl > MAX_SHLVL)
		shlvl_too_high(new_shlvl, kvp);
}

void	set_shlvl(t_node *head)
{
	char	*tmp;
	t_dict	*kvp;

	tmp = ft_itoa(1);
	kvp = new_kvp("SHLVL", tmp);
	free(tmp);
	if (kvp)
		ll_push(&head, ll_new(kvp));
}

void	update_shlvl(t_node *head)
{
	t_dict	*kvp;
	int		old_shlvl;
	int		new_shlvl;

	kvp = get_kvp(head, "SHLVL");
	if (kvp)
	{
		old_shlvl = ft_atoi(kvp->value);
		free(kvp->value);
		new_shlvl = old_shlvl + 1;
		if (new_shlvl < 0)
			kvp->value = ft_strdup("0");
		else if (new_shlvl >= MAX_SHLVL)
			handle_shlvl_limit(new_shlvl, &kvp);
		else
			kvp->value = ft_itoa(old_shlvl + 1);
	}
	else
		set_shlvl(head);
}

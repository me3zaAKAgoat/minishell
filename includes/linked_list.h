/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:50:37 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/16 02:52:12 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_node {
	void			*content;
	struct s_node	*next;
}	t_node;

extern	void		ll_push(t_node **head_p, t_node *new);
extern	void		ll_unshift(t_node **head_p, t_node *new);
extern	void		ll_clear(t_node	**head, void (free_content)(void *));
extern	void		ll_del_one(t_node *node, void (free_content)(void *));
extern	void		ll_iter(t_node	*head, void (f)(void	*));
extern	t_node	*ll_last(t_node	*head);
extern	t_node	*ll_new(void	*content);
extern	int		ll_size(t_node *head);
extern	t_node	*ll_map(t_node	*head, void *(f)(void	*),
						void (free_content)());
extern	int		ll_get_index(t_node	*head, t_node *node);
extern	t_node	*ll_atindex(t_node *head, int index);
extern	t_node	*ll_pop(t_node **head_p, int index);
extern	t_node	*ll_shift(t_node **head_p);

#endif
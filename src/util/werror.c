/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   werror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 02:17:38 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/20 02:55:50 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	werror(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

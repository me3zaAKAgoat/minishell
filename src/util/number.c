/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:12:33 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/21 21:27:50 by echoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!(48 <= str[i] && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	long long	return_number;
	int			i;
	int			sign;

	i = 0;
	return_number = 0;
	sign = 1;
	while ((str[i] <= 13 && 9 <= str[i]) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
		return_number = return_number * 10 + (str[i++] - 48);
	return (sign * return_number);
}

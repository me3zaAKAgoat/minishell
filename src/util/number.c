/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoukri <echoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:12:33 by echoukri          #+#    #+#             */
/*   Updated: 2023/06/28 20:02:24 by echoukri         ###   ########.fr       */
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

int	overflows(long long n, int sign, char digit)
{
	return ((sign == 1
			&& (n > (LLONG_MAX - (digit - '0')) / 10))
		|| (sign == -1
			&& (-n < (LLONG_MIN + (digit - '0')) / 10)));
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
	{
		if (overflows(return_number, sign, str[i]))
			errno = EOVERFLOW;
		return_number = return_number * 10 + (str[i++] - 48);
	}
	return (sign * return_number);
}

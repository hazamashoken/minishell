/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:40:11 by abossel           #+#    #+#             */
/*   Updated: 2022/08/25 10:52:29 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n')
		return (1);
	if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

/*
 * state:
 * 1 - space section
 * 2 - plus and minus section
 * 3 - number section
 */
int	ft_atoi(const char *str)
{
	int	state;
	int	number;
	int	negative;

	state = 1;
	number = 0;
	negative = -1;
	while (*str != '\0')
	{
		if (state <= 3 && ft_isdigit(*str))
		{
			state = 3;
			number = (number * 10) - (*str - '0');
		}
		else if (state <= 2 && (*str == '+' || *str == '-'))
		{
			state = 3;
			if (*str == '-')
				negative = -negative;
		}
		else if (state != 1 || !ft_is_space(*str))
			break ;
		str++;
	}
	return (number * negative);
}

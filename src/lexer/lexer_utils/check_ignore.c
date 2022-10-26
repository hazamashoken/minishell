/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ignore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:18:44 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:37:16 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_special_char(char c)
{
	return (
		c == '>' || c == '<' || c == '|' || c == '&'
	);
}

int	has_special_char(char *str)
{
	int	i;

	i = -1;
	while (*(str + ++i))
		if (is_special_char(*(str + i)))
			return (1);
	return (0);
}

int	find_special(char *str)
{
	int	i;

	i = -1;
	while (*(str + ++i))
	{
		if (is_special_char(*(str + i)))
			return (i);
	}
	return (i);
}

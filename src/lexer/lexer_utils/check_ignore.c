/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ignore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:18:44 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/08 23:08:10 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

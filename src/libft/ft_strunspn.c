/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strunspn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:57:02 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/07 14:58:37 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strunspn(char *str, char *reject)
{
	int	i;

	i = 0;
	while (*(str + i) && !ft_strchr(reject, *(str + i)))
		i++;
	if (i == ft_strlen(str) && ft_strchr(reject, *(str + i)))
		return (-1);
	return (i);
}

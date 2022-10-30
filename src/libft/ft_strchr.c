/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:49:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/27 22:20:47 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

char	*ft_strchr(char *s, int c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (s);
}

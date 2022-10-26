/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:40 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:38:29 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	if (!haystack && len == 0)
		return (NULL);
	i = 0;
	if (!*needle)
		return (haystack);
	while (*(haystack + i) && i < len)
	{
		k = 0;
		while (*(haystack + i + k) == *(needle + k) && i + k < len)
		{
			if (*(needle + k + 1) == '\0')
				return (haystack + i);
			k++;
		}
		i++;
	}
	return (0);
}

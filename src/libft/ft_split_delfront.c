/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delfront.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:43:42 by abossel           #+#    #+#             */
/*   Updated: 2022/10/03 11:35:19 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_split_delfront(char **words)
{
	int	i;

	if (words != NULL)
	{
		if (words[0] != NULL)
			free(words[0]);
		i = 0;
		while (words[i] != NULL)
		{
			words[i] = words[i + 1];
			i++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokensize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:32:12 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:56:47 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_tokensize(t_token *lst)
{
	size_t	size;
	t_token	*node;

	node = lst;
	size = 0;
	while (node != NULL)
	{
		//printf("p: %p\n", node);
		node = node->next;
		size++;
	}
	return (size);
}

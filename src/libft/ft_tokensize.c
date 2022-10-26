/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokensize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:32:12 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:41:09 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:31:47 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/26 12:41:01 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*node;

	if (new == NULL)
		return ;
	node = *lst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
		new->prev = node;
	}
	else
		*lst = new;
}

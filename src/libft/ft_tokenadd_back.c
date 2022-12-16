/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:31:47 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/09 11:42:15 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

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

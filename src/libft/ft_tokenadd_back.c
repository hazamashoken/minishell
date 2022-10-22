/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:31:47 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/22 11:45:52 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../../cadet/minishell/includes/minishell.h"

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*node;

	node = *lst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
	else
		*lst = new;
}

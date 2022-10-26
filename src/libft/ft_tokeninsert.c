/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeninsert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:30:36 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:39:13 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

int	ft_tokeninsert(t_token **head, t_token *new, int index)
{
	int		size;
	t_token	*tmp;

	if (new == NULL)
		return (1);
	size = ft_tokensize(*head);
	if (index < 0 || index > size)
		return (1);
	else if (head == NULL)
		*head = new;
	else if (index == 0)
		ft_tokenadd_front(head, new);
	else if (index == size)
		ft_tokenadd_back(head, new);
	else
	{
		tmp = *head;
		while (--index)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next->prev = new;
		new->prev = tmp;
		tmp->next = new;
	}
	return (0);
}

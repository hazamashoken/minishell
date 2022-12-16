/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeninsert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:30:36 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:56:31 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

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

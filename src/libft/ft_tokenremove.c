/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenremove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:42:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/24 13:33:14 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

void	ft_tokenremove(t_token *head, int index)
{
	int		size;
	t_token	*tmp;

	size = ft_tokensize(head);
	if (index < 0 || index > size)
		return ;
	tmp = head;
	while (index--)
		tmp = tmp->next;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	ft_tokendelone(tmp);
}

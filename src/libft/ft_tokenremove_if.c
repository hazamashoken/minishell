/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenremove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:47:25 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:56:42 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenremove_if(t_token *begin_list,
	void *data_ref, int (*cmp)(char *, int))
{
	t_token	*cur;

	if (begin_list == NULL)
		return ;
	cur = begin_list;
	if (cmp(data_ref, *cur->token) == 1)
	{
		if (cur->prev)
			cur->prev->next = cur->next;
		if (cur->next)
			cur->next->prev = cur->prev;
		ft_tokendelone(cur);
		ft_tokenremove_if(begin_list, data_ref, cmp);
	}
	cur = begin_list;
	ft_tokenremove_if(cur->next, data_ref, cmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:02:35 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:56:24 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenclear(t_token **lst)
{
	t_token	*cur;
	t_token	*next;

	if (lst == NULL)
		return (1);
	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->token);
		free(cur);
		cur = next;
	}
	*lst = NULL;
	return (1);
}

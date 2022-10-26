/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:02:35 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:39:00 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		//printf("free: %p\n", cur);
		free(cur->token);
		free(cur);
		cur = next;
	}
	*lst = NULL;
	return (1);
}

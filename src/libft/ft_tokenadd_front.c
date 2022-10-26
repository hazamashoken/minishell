/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:37:30 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/26 09:44:46 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tokenadd_front(t_token **lst, t_token *new)
{
	if (*lst && new != NULL)
	{
		new->next = *lst;
		(*lst)->prev = new;
		*lst = new;

	}
	else if (new != NULL)
		*lst = new;
}

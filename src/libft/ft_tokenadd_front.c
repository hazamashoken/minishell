/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:37:30 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/14 14:52:35 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

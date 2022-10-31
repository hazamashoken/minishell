/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeninject.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:25:53 by abossel           #+#    #+#             */
/*   Updated: 2022/10/31 23:35:43 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** injects new_front in front of token by copying memory
** this allows you to add to the front with t_token**
*/
int    ft_tokeninject(t_token *token, t_token *new_front)
{
    t_token tmp;
    t_token *old_front;

    if (token == NULL || new_front == NULL || token == new_front)
        return (0);
    ft_memcpy(&tmp, token, sizeof(t_token));
    ft_memcpy(token, new_front, sizeof(t_token));
    ft_memcpy(new_front, &tmp, sizeof(t_token));
    old_front = new_front;
    token->next = old_front;
    token->prev = old_front->prev;
    if (old_front->next != NULL)
        old_front->next->prev = old_front;
    old_front->prev = token;
    return (1);
}
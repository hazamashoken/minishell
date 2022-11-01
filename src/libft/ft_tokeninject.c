/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeninject.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:25:53 by abossel           #+#    #+#             */
/*   Updated: 2022/11/01 12:58:49 by abossel          ###   ########.fr       */
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

    if (token == NULL || new_front == NULL || token == new_front)
        return (0);
    new_front->next = new_front;
    new_front->prev = token->prev;
    if (token->next != NULL)
        token->next->prev = new_front;
    token->prev = token;
    ft_memcpy(&tmp, token, sizeof(t_token));
    ft_memcpy(token, new_front, sizeof(t_token));
    ft_memcpy(new_front, &tmp, sizeof(t_token));
    return (1);
}
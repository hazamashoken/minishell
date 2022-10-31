/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_after.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:46:58 by abossel           #+#    #+#             */
/*   Updated: 2022/10/31 23:51:02 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** inserts after behind token
*/
int ft_tokenadd_after(t_token *token, t_token *after)
{
    if (token == NULL || after == NULL || token == after)
        return (0);
    after->next = token->next;
    if (token->next != NULL)
        token->next->prev = after;
    token->next = after;
    after->prev = token;
    return (1);
}
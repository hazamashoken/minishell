/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_priority.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:53:07 by abossel           #+#    #+#             */
/*   Updated: 2022/11/01 01:56:25 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expander_set_priority(t_token *tok)
{
    int     priority;

    priority = 0;
    while(tok != NULL)
    {
        if (tok->type == OPEN)
            priority++;
        if (priority < 0)
            return (0);
        tok->piority = priority;
        if (tok->type == CLOSE)
            priority--;
        tok = tok->next;
    }
    return (1);
}

t_token *find_highest_priority(t_token *tok)
{
    t_token *node;
    int     max;

    if (tok == NULL)
        return (NULL);
    node = tok;
    max = tok->piority;
    while (tok != NULL)
    {
        if (tok->piority > max)
        {
            node = tok;
            max = tok->piority;
        }
        tok = tok->next;
    }
    return (node);
}

t_token *find_priority_end(t_token *tok)
{
    t_token *node;

    if (tok == NULL)
        return (NULL);
    node = tok;
    while (node->next != NULL)
    {
        if (node->next->piority != node->piority)
            return (node);
        node = node->next;
    }
    return (node);
}
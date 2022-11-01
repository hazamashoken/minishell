/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_priority.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:53:07 by abossel           #+#    #+#             */
/*   Updated: 2022/11/01 13:27:07 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_set_priority(t_env *env)
{
    int     priority;
    t_token *tok;

    priority = 0;
    tok = env->token;
    while(tok != NULL)
    {
        if (tok->type == OPEN_P)
            priority++;
        if (priority < 0)
            return (0);
        tok->piority = priority;
        if (tok->type == CLOSE_P)
            priority--;
        tok = tok->next;
    }
    return (1);
}

static t_token *find_highest_priority(t_token *tok)
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

static t_token *find_priority_end(t_token *tok)
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

/*
** sets start and end to the start and end tokens with highest priority.
** returns 1 if tokens found or 0 if token list is empty
*/
int expand_get_highest_priority(t_env *env, t_token **start, t_token **end)
{
    *start = find_highest_priority(env->token);
    *end = NULL;
    if (*start != NULL)
    {
        *end = find_priority_end(*start);
        if (*end != NULL)
            return (1);
    }
    return (0);
}
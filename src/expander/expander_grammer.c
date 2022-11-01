/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_grammer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:04:08 by abossel           #+#    #+#             */
/*   Updated: 2022/11/01 13:25:01 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_andor(int type)
{
    if (type == AND || type == OR)
        return (1);
    return (0);
}

static int  is_cmdarg(int type)
{
    if (type == CMD || type == ARG)
        return (1);
    return (0);
}

static int check_grammer_meta(t_token *t)
{
    int p;
    int n;

    p = EMPTY;
    if (t->prev != NULL)
        p = t->prev->type;
    n = EMPTY;
    if (t->next != NULL)
        n = t->next->type;
    if (is_andor(t->type) && (p == OPEN_P || n == CLOSE_P))
        return (0);
    if (is_andor(t->type) && (p == EMPTY || n == EMPTY))
        return (0);
    if (is_andor(t->type) && (is_andor(p) || is_andor(n)))
        return (0);
    if (t->type == OPEN_P && (n == CLOSE_P || n == EMPTY || is_cmdarg(p)))
        return (0);
    if (t->type == CLOSE_P && (n == OPEN_P || p == EMPTY || is_cmdarg(n)))
        return (0);
    return (1);
}

int expand_check_grammer(t_env *env)
{
    t_token *node;

    node = env->token;
    while (node != NULL)
    {
        if (!check_grammer_meta(node))
        {
            // TODO: syntax error message here
            return (0);
        }
        node = node->next;
    }
    return (1);
}
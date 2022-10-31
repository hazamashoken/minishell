/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_grammer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:04:08 by abossel           #+#    #+#             */
/*   Updated: 2022/11/01 02:01:10 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int check_grammer_end(t_token *tok, t_token *start)
{
    return (0);
}

void    is_valid_token(char *s)
{
    if (s == NULL)
        return (0);
    if (*s == '\0')
        return (0);
    if (ft_strncmp("()", s, 3) == 0)
        return (0);
    return (1);
}

int check_grammer_cmd(t_token *tok, int priority, int open, int close)
{
    int next_priority;

    if (!is_valid_token(tok->token))
        return (0);
    if (remove_open_par(tok->token))
        return(check_grammer_cmd(tok, priority + 1), open + 1, close);
    tok->piority = priority;
    if (remove_close_par(tok->token))
    {
        if (token->next == NULL && open == close - 1)
            return (1);
        if (token->next->type == AND || token->next->type == OR)
            return (check_grammer_andor(tok, priority - 1, open, close - 1));
    }
}

int check_grammer_middle(t_token *tok, t_token *start)
{
    if (tok == NULL)
        check_grammer_end(tok->prev, start);
    if (tok->type == CMD)
        return (check_grammer_middle(tok->next, start));
    if (tok->type == PIPE)
        return (check_grammer_middle(tok->prev, start));
    if (tok->type == AND || tok->type == OR)
        return (check_grammer_end(tok->prev, start));
    return (check_grammer_middle(tok->next, start));
}

int check_grammer_start(t_token *tok, t_token *end)
{
    if (tok == NULL)
        return (1);
    if (tok->type == CMD)
        return (check_grammer_middle(tok->next, end));
    if (tok->type == INPUT || tok->type == TRUNC || tok->type == APPEND)
        return (check_grammer_start(tok->next, end));
    return (0);
}

int check_grammer(t_token *start, t_token *end)
{
    int     state;
    t_token *node;

    if (start == NULL || end == NULL)
        return (1);
    node = start;
    state = 0;
    return (0);
}
*/
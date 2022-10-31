/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_parentheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:27:33 by abossel           #+#    #+#             */
/*   Updated: 2022/11/01 00:34:47 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int remove_open_par(char *s)
{
    if (s == NULL)
        return (0);
    if (s[0] == '(')
    {
        while (s[0] != '\0')
        {
            s[0] = s[1];
            s++;
        }
        return (1);
    }
    return (0);
}

int remove_close_par(char *s)
{
    int len;

    if (s == NULL)
        return (0);
    len = ft_strlen(s);
    if (len == 0)
        return (0);
    if (s[len - 1] == ')')
    {
        s[len - 1] = '\0';
        return (1);
    }
    return (0);
}

int expander_parentheses(t_token *tok)
{
    t_token *t;

    if (tok == NULL)
        return (1);
    if (tok->type != CLOSE && remove_open_par(tok->token))
    {
        t = ft_tokennew(ft_strdup("("), OPEN);
        if (t == NULL)
            return (0);
        ft_tokeninject(tok, t);
        return (expander_parentheses(tok->next));
    }
    if (tok->type != CLOSE && remove_close_par(tok->token))
    {
        t = ft_tokennew(ft_strdup(")"), CLOSE);
        if (t == NULL)
            return (0);
        ft_tokenadd_after(tok, t);
        return (expander_parentheses(tok));
    }
    return (expander_parentheses(tok->next));
}

int expand_parentheses_tokens(t_env *env)
{
    if (env->token != NULL)
        return (expander_parentheses(env->token));
    return (1);
}
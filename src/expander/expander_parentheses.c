/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_parentheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:27:33 by abossel           #+#    #+#             */
/*   Updated: 2022/11/01 13:03:03 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** remove the ( at the start of the string
*/
static int remove_open_par(char *s)
{
    int i;

    if (s == NULL)
        return (0);
    if (s[0] == '(')
    {
        i = 0;
        while (s[i] != '\0')
        {
            s[i] = s[i + 1];
            i++;
        }
        return (1);
    }
    return (0);
}

/*
** remove the ) if at the end of the string
*/
static int remove_close_par(char *s)
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

/*
** convert a token with a single parentheses to a OPEN or CLOSE type
** TODO: check if single or double quote
*/
static int  convert_par(t_token *tok)
{
    if (tok->type == OPEN_P || tok->type == CLOSE_P)
        return (0);
    if (ft_strncmp("(", tok->token, 2) == 0)
    {
        tok->type = OPEN_P;
        return (1);
    }
    if (ft_strncmp(")", tok->token, 2) == 0)
    {
        tok->type = CLOSE_P;
        return (1);
    }
    return (0);
}

/*
** remove the parentheses from the satrt and end of each token string and
** convert them to OPEN and CLOSE types
** TODO: check if single and double quotes
*/
int expander_parentheses(t_token *tok)
{
    t_token *t;

    if (tok == NULL)
        return (1);
    if (convert_par(tok))
        return (expander_parentheses(tok->next));
    if (tok->type != OPEN_P && remove_open_par(tok->token))
    {
        t = ft_tokennew(ft_strdup("("), OPEN_P);
        if (t == NULL)
            return (0);
        ft_tokeninject(tok, t);
        return (expander_parentheses(tok->next));
    }
    if (tok->type != CLOSE_P && remove_close_par(tok->token))
    {
        t = ft_tokennew(ft_strdup(")"), CLOSE_P);
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
    {
        return (expander_parentheses(env->token));
    }
    return (1);
}
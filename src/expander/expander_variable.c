/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:51:19 by abossel           #+#    #+#             */
/*   Updated: 2022/11/01 11:14:32 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_brace(char *pos)
{
    if (!ft_isalpha(*pos))
        return (0);
    while (*pos != '\0' && *pos != '}')
    {
        if (!ft_isalnum(*pos))
            return (0);
        pos++;
    }
    if (*pos == '\0')
        return (0);
    return (1);
}

/*
** Get an env var with a start and end string pointer.
** pos is the first char in the name. end is after the last char.
*/
static char    *get_env_variable(char *pos, char *end)
{
    char    *env;
    char    old;

    old = *end;
    *end = '\0';
    env = getenv(pos);
    *end = old;
    return (env);
}

static char *bad_sub_error(char *token)
{
    // TODO: print bad substitution message;
    return (NULL);
}

char    *expand_brace(char *token, char *pos, char **next_pos)
{
    char    *expand;
    char    zero;
    char    *end;
    char    *env;
    int     size;

    zero = '\0';
    if (!is_valid_brace(pos + 2))
        return (bad_sub_error(token));
    end = ft_strchr(pos, '}');
    env = get_env_variable(pos + 2, end);
    if (env == NULL)
        env = &zero;
    size = ft_strlen(token) + ft_strlen(env) + 1;
    expand = malloc(size);
    if (expand == NULL)
        return (NULL);
    *pos = '\0';
    ft_strlcpy(expand, token, size);
    ft_strlcat(expand, env, size);
    *next_pos = ft_strchr(expand, '\0');
    ft_strlcat(expand, end + 1, size);
    return (expand);
}

char    *expand_var(char *token, char *pos, char **next_pos)
{
    char    *expand;
    char    zero;
    char    *end;
    char    *env;
    int     size;

    zero = '\0';
    if (!ft_isalpha(pos[1]))
        return (NULL);
    end = pos + 1;
    while (ft_isalnum(*end) && *end != '\0')
        end++;
    env = get_env_variable(pos + 1, end);
    if (env == NULL)
        env = &zero;
    size = ft_strlen(token) + ft_strlen(env) + 1;
    expand = malloc(size);
    if (expand == NULL)
        return (NULL);
    *pos = '\0';
    ft_strlcpy(expand, token, size);
    ft_strlcat(expand, env, size);
    *next_pos = ft_strchr(expand, '\0');
    ft_strlcat(expand, end, size);
    return (expand);
}
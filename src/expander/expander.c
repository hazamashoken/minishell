/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:02 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/11 21:29:04 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Expand the $? meta char.
** Size is strlen - 2 (meta char) + 11 (max int size) + 1 (terminator)
*/
char	*expand_error(t_env *env, char *token, char *pos, char **next_pos)
{
	char	*expand;
	char	*errnum;
	int		size;

	size = ft_strlen(token) - 2 + 11 + 1;
	expand = malloc(size);
	if (expand == NULL)
		return (NULL);
	*pos = '\0';
	pos += 2;
	if (ft_strncmp("${?}", pos, 4) == 0)
		pos += 2;
	ft_strlcpy(expand, token, size);
	errnum = ft_itoa(env->ret);
	ft_strlcat(expand, errnum, size);
	free(errnum);
	*next_pos = ft_strchr(expand, '\0');
	ft_strlcat(expand, pos, size);
	return (expand);
}

static char	*expand_token(t_env *env, char *token, char *pos, char **next_pos)
{
	char	*expand;

	expand = NULL;
	if (ft_strncmp("${?}", pos, 4) == 0)
		expand = expand_error(env, token, pos, next_pos);
	else if (ft_strncmp("$?", pos, 2) == 0)
		expand = expand_error(env, token, pos, next_pos);
	else if (ft_strncmp("${", pos, 2) == 0)
		expand = expand_brace(token, pos, next_pos);
	else
		expand = expand_var(token, pos, next_pos);
	if (expand == NULL)
		*next_pos = pos + 1;
	return (expand);
}

static int	is_expandable_variable(t_token *tok)
{
	if (tok->quote == SINGLE_Q)
		return (0);
	return (1);
}

static void	swap_token(t_token *current, char *expand)
{
	free(current->token);
	current->token = expand;
}

int	expand_variable_tokens(t_env *env)
{
	t_token	*current;
	char	*expand;
	char	*pos;
	char	*next_pos;

	current = env->token;
	while (current != NULL)
	{
		if (is_expandable_variable(current))
		{
			pos = ft_strchr(current->token, '$');
			while (pos != NULL)
			{
				expand = expand_token(env, current->token, pos, &next_pos);
				if (expand != NULL)
					swap_token(current, expand);
				else
					return (0);
				pos = ft_strchr(next_pos, '$');
			}
		}
		current = current->next;
	}
	return (1);
}

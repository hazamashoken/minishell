/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:20:58 by abossel           #+#    #+#             */
/*   Updated: 2022/12/16 12:21:49 by abossel          ###   ########.fr       */
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

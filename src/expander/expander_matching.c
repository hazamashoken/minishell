/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_matching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:12:16 by abossel           #+#    #+#             */
/*   Updated: 2022/10/26 13:01:05 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	match_before(char *filename, char *pattern);
static int	match_after(char *filename, char *pattern);

static int	next_wildcard(char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i] != '*' && pattern[i] != '\0')
		i++;
	return (i);
}

/*
** matches a string before the wildcard
** will call match_after if the filename matches the first part of the pattern
*/
static int	match_before(char *filename, char *pattern)
{
	int	i;

	i = next_wildcard(pattern);
	if (ft_strncmp(filename, pattern, i) == 0)
	{
		if (filename[i] == '\0' && pattern[i] == '\0')
			return (1);
		if (filename[i] != '\0' && pattern[i] == '\0')
			return (0);
		return (match_after(filename + i, pattern + i));
	}
	return (0);
}

/*
** matches a string after the wildcard
** will call match_before to match the next part of the pattern
*/
static int	match_after(char *filename, char *pattern)
{
	int	i;

	while (pattern[0] == '*')
		pattern++;
	if (pattern[0] == '\0')
		return (1);
	i = 0;
	while (filename[i] != '\0')
	{
		if (match_before(filename + i, pattern))
			return (1);
		i++;
	}
	return (0);
}

/*
** returns 1 if filename matches the wildcard pattern or 0 otherwise
*/
int	match_wildcard(char *filename, char *pattern)
{
	if (pattern[0] != '*')
		return (match_before(filename, pattern));
	return (match_after(filename, pattern));
}
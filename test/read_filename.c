/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:45:37 by abossel           #+#    #+#             */
/*   Updated: 2022/10/23 23:55:35 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include "libft.h"

int	is_end(char *s)
{
	if (*s == '<' || *s == '>' || *s == '|' || *s == ' ' || *s == '\0')
		return (1);
	return (0);
}

char	*read_escape(char *dst, char *src)
{
	if (*src != '\\')
		return (NULL);
	src++;
	if (*src == '\\' || *src == '"' || *src ==  '\'')
	{
		*dst = *src;
		dst++;
		*dst = '\0';
		return (src);
	}
	return (NULL);
}

char	*read_single_quote(char *dst, char *src)
{
	if (*src != '\'')
		return (NULL);
	src++;
	while (*src != '\'')
	{
		if (*src == '\0')
			return (NULL);
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (src);
}

char	*read_double_quote(char *dst, char *src)
{
	if (*src != '"')
		return (NULL);
	src++;
	while (*src != '"')
	{
		if (*src == '\0')
			return (NULL);
		else if (*src == '\\')
		{
			src = read_escape(dst, src);
			if (src == NULL)
				return (NULL);
		}
		else
			*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (src);
}

/*
** read a file name from a string until <, >, |, space or end of string
** ignoring escape characters and quotes
** returns NULL if no filename or error
*/
char	*read_filename(char *dst, char *src)
{
	while (*src == ' ')
		src++;
	if (is_end(src))
		return (NULL);
	while (!is_end(src))
	{
		if (*src == '\\')
			src = read_escape(dst, src);
		else if (*src == '\'')
			src = read_single_quote(dst, src);
		else if (*src == '"')
			src = read_double_quote(dst, src);
		else
		{
			*dst = *src;
			dst++;
			*dst = '\0';
		}
		if (src == NULL)
			return (NULL);
		src++;
		dst = dst + ft_strlen(dst);
	}
	return (src);
}

int	main(void)
{
	char	dst[1000];
	char	*src = "  start\\\\-\"\\\\double\\\"\"-\'single\\\\\'-\"  \"-\"\'end\'\"";

	dst[0] = '\0';
	if (read_filename(dst, src) == NULL)
		printf("KO\n");
	else
	{
		printf("OK\n");
		printf("|%s|\n|%s|\n", src, dst);
	}
	return (0);
}

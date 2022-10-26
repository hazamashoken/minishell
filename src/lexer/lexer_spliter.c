/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_spliter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:15:59 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:37:33 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	alloc_size(char *line, int pos)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	while (*(line + pos + i) && (*(line + pos + i) != ' ' || c != ' '))
	{
		if (c == ' ' && (*(line + pos + i) == '\''
				|| *(line + pos + i) == '\"'))
			c = *(line + pos + i);
		else if (c != ' ' && *(line + pos + i) == c)
			c = ' ';
		i++;
	}
	return (i + 1);
}

static char	*get_token(char *line, int *pos, int *error)
{
	char	*token_str;
	int		i;
	char	c;

	i = 0;
	c = ' ';
	token_str = malloc(sizeof(char) * alloc_size(line, *pos));
	if (token_str == NULL)
		return (NULL);
	while (*(line + *pos) && (*(line + *pos) != ' ' || c != ' '))
	{
		if (c == ' ' && (*(line + *pos) == '\'' || *(line + *pos) == '\"'))
			c = *(line + *pos);
		else if (c != ' ' && *(line + *pos) == c)
			c = ' ';
		*(token_str + (i)++) = *(line + (*pos)++);
	}
	*(token_str + i) = '\0';
	if (c != ' ')
	{
		free (token_str);
		*error = i;
		return (NULL);
	}
	return (token_str);
}

static void	skip_whitespace(char *str, int *pos)
{
	while (ft_isspace(*(str + *pos)) == 1)
		(*pos)++;
	(*pos)--;
}

int	lexer_spliter(char *line, t_env *env)
{
	int		pos;
	t_token	*token;
	int		error;

	pos = -1 ;
	error = 0;
	skip_whitespace(line, &pos);
	while (*(line + ++pos))
	{
		token = ft_tokennew(get_token(line, &pos, &error), EMPTY);
		if (token == NULL)
		{
			if (error)
				printf("minihell: parse error at %c\n", *(line + pos - error));
			return (ft_tokenclear(&env->token));
		}
		ft_tokenadd_back(&env->token, token);
		if (*(line + pos) == 0)
			break ;
	}
	return (0);
}

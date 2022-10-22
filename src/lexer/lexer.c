/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:05 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/22 17:13:17 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

/*
@brief		check for ' " \ and return the token size need to be malloc"
@return		size_t 	size to be malloc
*/
size_t	alloc_size(char *line, int pos)
{
	size_t	size;
	int		i;
	char	c;

	size = 0;
	i = 0;
	c = ' ';
	while (*(line + pos) && (*(line + pos + i) != ' ' || c != ' '))
	{
		if (c == ' ' && (*(line + pos + i) == '\''
				|| *(line + pos + i) == '\"'))
			c = *(line + pos + i++);
		else if (c != ' ' && *(line + pos + i) == c)
		{
			size += 2;
			c = ' ';
			i++;
		}
		else
			i++;
		if (*(line + pos + i - 1) == '\\')
			size--;
	}
	return (i - size + 1);
}

/*
@brief put token without ' " \ into new malloced string"
@return char *  new token string
*/
char	*get_token(char *line, int *pos)
{
	char	*token_str;
	char	c;
	int		i;

	i = 0;
	c = ' ';
	token_str = malloc(sizeof(char) * alloc_size(line, *pos));
	if (token_str == NULL)
		return (NULL);
	while (*(line + *pos) && (*(line + *pos) != ' ' || c != ' '))
	{
		if (c == ' ' && (*(line + *pos) == '\'' || *(line + *pos) == '\"'))
			c = *(line + (*pos)++);
		else if (c != ' ' && *(line + *pos) == c)
		{
			c = ' ';
			(*pos)++;
		}
		else if (*(line + *pos) == '\\' && (*pos)++)
			*(token_str + i++) = *(line + (*pos)++);
		else
			*(token_str + i++) = *(line + (*pos)++);
	}
	*(token_str + i) = '\0';
	return (token_str);
}

//Move inital whitespace
void	skip_whitespace(char *line, int *pos)
{
	while (ft_isspace(*(line + *pos)) == 1)
		(*pos)++;
}

//Put token into linked link in env
int	lexer_spliter(char *line, t_env *env)
{
	int		pos;
	char	*part;
	t_token	*token;

	pos = 0 ;
	skip_whitespace(line, &pos);
	while (*(line + pos))
	{
		part = get_token(line, &pos);
		if (part == NULL)
			return (1);
		token = ft_tokennew(part, EMPTY);
		if (token == NULL)
			return (ft_tokenclear(&env->token));
		ft_tokenadd_back(&env->token, token);
		pos++;
	}
	ft_tokenprint(env);
	return (0);
}

int	lexer(char *line, t_env *env)
{
	if (lexer_spliter(line, env) == 1)
		return (1);
	return (0);
}

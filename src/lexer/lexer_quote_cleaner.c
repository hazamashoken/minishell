/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_cleaner.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:17:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/24 20:48:38 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

static size_t	alloc_size(char *line)
{
	int		i;
	int		minus;
	char	c;

	i = 0;
	minus = 0;
	c = ' ';
	while (*(line + i) && (*(line + i) != ' ' || c != ' '))
	{
		if (c == ' ' && (*(line + i) == '\'' || *(line + i) == '\"'))
			c = *(line + i);
		else if (c != ' ' && *(line + i) == c)
		{
			minus += 2;
			c = ' ';
		}
		i++;
	}
	return (i - minus + 1);
}

int	remove_quote(t_token *t)
{
	char	*dequote;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = ' ';
	dequote = malloc(sizeof(char) * alloc_size(t->token));
	if (dequote == NULL)
		return (1);
	while (*(t->token + i) && (*(t->token + i) != ' ' || c != ' '))
	{
		if (c == ' ' && (*(t->token + i) == '\'' || *(t->token + i) == '\"'))
			c = *(t->token + i++);
		else if (c != ' ' && *(t->token + i) == c)
		{
			i++;
			if (c == '\"')
				t->quote = DOUEBLE_Q;
			c = ' ';
		}
		else
			*(dequote + j++) = *(t->token + i++);
	}
	*(dequote + j) = '\0';
	free(t->token);
	t->token = dequote;
	return (0);
}

int	quote_cleaner(t_env *env)
{
	t_token	*tmp;

	tmp = env->token;
	while (tmp)
	{
		remove_quote(tmp);
		tmp = tmp->next;
	}
	return (0);
}


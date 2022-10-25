/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_cleaner.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:17:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 09:15:29 by tliangso         ###   ########.fr       */
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

void	init_runner(t_runner *r)
{
	r->i = 0;
	r->j = 0;
	r->c = ' ';
}

int	remove_quote(t_token *t)
{
	t_runner	r;

	init_runner(&r);
	r.deqstr = malloc(sizeof(char) * alloc_size(t->token));
	if (r.deqstr == NULL)
		return (1);
	while (*(t->token + r.i) && (*(t->token + r.i) != ' ' || r.c != ' '))
	{
		if (r.c == ' ' && (*(t->token + r.i) == '\''
				|| *(t->token + r.i) == '\"'))
			r.c = *(t->token + r.i++);
		else if (r.c != ' ' && *(t->token + r.i) == r.c)
		{
			r.i++;
			if (r.c == '\"' && r.i++)
				t->quote = DOUEBLE_Q;
			r.c = ' ';
		}
		else
			*(r.deqstr + r.j++) = *(t->token + r.i++);
	}
	*(r.deqstr + r.j) = '\0';
	free(t->token);
	t->token = r.deqstr;
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

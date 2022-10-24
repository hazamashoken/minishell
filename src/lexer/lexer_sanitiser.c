/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_sanitiser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:11:15 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/24 20:51:47 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

int	check_double(char *str, int str_index)
{
	if (str_index == 0)
	{
		if (*(str + str_index) == *(str + str_index + 1))
			return (1);

	}
	else if (str_index == 1)
	{
		if (*(str + str_index) == *(str + str_index - 1))
			return (1);
	}
	return (0);
}

static int	split_special(t_env *env, char *str, int str_index, int *list_index)
{
	int	size;

	size = 1;
	if (check_double(str, str_index))
		size = 2;
	if (str_index == 0)
	{
		if (ft_tokeninsert(&env->token,
				ft_tokennew(ft_strdup(str + size), EMPTY), *(list_index)))
			return (-1);
		if (ft_tokeninsert(&env->token,
				ft_tokennew(ft_strndup(str, size), EMPTY), *(list_index)))
			return (-1);
	}
	else
	{
		if (ft_tokeninsert(&env->token,
				ft_tokennew(ft_strdup(str + str_index), EMPTY), *(list_index)))
			return (-1);
		if (ft_tokeninsert(&env->token,
				ft_tokennew(ft_strndup(str, str_index), EMPTY), *(list_index)))
			return (-1);
	}
	ft_tokenremove(env->token, ++*(list_index) + 1);
	return (1);
}

static int	check_quote(t_env *env, t_token **token, int *list_idx)
{
	char	c;
	int		i;

	c = ' ';
	i = -1;
	while (*((*token)->token + ++i))
	{
		if (c == ' ' && (*((*token)->token + i) == '\''
				|| *((*token)->token + i) == '\"'))
			c = *((*token)->token + i);
		else if (c != ' ' && *((*token)->token + i) == c)
			c = ' ';
		else if (c == ' ' && is_special_char(*((*token)->token + i)))
		{
			if (has_special_char((*token)->token)
				&& ((ft_strlen((*token)->token) > 2
						&& check_double((*token)->token, i))
					|| (ft_strlen((*token)->token) > 1
						&& !check_double((*token)->token, i)))
				&& !(check_double((*token)->token, i)
					&& ft_strlen((*token)->token) == 2))
				return (split_special(env, (*token)->token, i, list_idx));
		}
	}
	return (0);
}

int	pre_sanitise(t_env *env)
{
	t_token	*tmp;
	int		list_index;
	int		back;

	list_index = -1;
	tmp = env->token;
	env->cur_token = tmp;
	while (tmp && ++list_index >= 0)
	{
		back = check_quote(env, &tmp, &list_index);
		if (back == -1)
			return (1);
		else if (back)
		{
			tmp = env->token;
			list_index = -1;
		}
		else
			tmp = tmp->next;
		env->cur_token = tmp;
	}
	return (0);
}

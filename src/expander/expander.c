/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:02 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/16 12:21:32 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;
	int		single_open;
	int		double_open;

	if (tok->quote == 0)
	{
		i = 0;
		single_open = 0;
		double_open = 0;
		while (tok->token[i] != '\0')
		{
			if (tok->token[i] == '\'' && !double_open)
				single_open = !single_open;
			if (tok->token[i] == '\"' && !single_open)
				double_open = !double_open;
			if (tok->token[i] == '$' && (ft_isalpha(tok->token[i + 1])
					|| tok->token[i + 1] == '?' || tok->token[i + 1] == '{' )
				&& !single_open)
				return (1);
			i++;
		}
	}
	return (0);
}

static int	swap_token(t_env *env, t_token *current, char *pos, char **next_pos)
{
	char	*expand;

	expand = expand_token(env, current->token, pos, next_pos);
	if (expand != NULL)
	{
		free(current->token);
		current->token = expand;
		return (1);
	}
	return (0);
}

static char	*find_next_var(char *token, int *s_open, int *d_open)
{
	int	single_open;
	int	double_open;
	int	i;

	i = 0;
	single_open = *s_open;
	double_open = *d_open;
	while (token[i] != '\0')
	{
		if (token[i] == '\'' && !double_open)
			single_open = !single_open;
		if (token[i] == '\"' && !single_open)
			double_open = !double_open;
		if (token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '?'
				|| token[i + 1] == '{' ) && !single_open)
		{
			*s_open = single_open;
			*d_open = double_open;
			return (&token[i]);
		}
		i++;
	}
	*s_open = single_open;
	*d_open = double_open;
	return (NULL);
}

int	expand_variable_tokens(t_env *env)
{
	t_token	*current;
	char	*pos;
	char	*next_pos;
	int		single_open;
	int		double_open;

	single_open = 0;
	double_open = 0;
	current = env->token;
	while (current != NULL)
	{
		if (is_expandable_variable(current))
		{
			pos = find_next_var(current->token, &single_open, &double_open);
			while (pos != NULL)
			{
				if (!swap_token(env, current, pos, &next_pos))
					return (0);
				pos = find_next_var(next_pos, &single_open, &double_open);
			}
		}
		current = current->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:22:45 by abossel           #+#    #+#             */
/*   Updated: 2022/12/14 14:59:42 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

/*
** Returns true is token lex has wildcards that can be expanded.
** Only cwd is expanded. Tokens with '/' are not expanded.
*/
static int	is_expandable(t_token *lex)
{
	if (lex->quote != SINGLE_Q)
	{
		if (ft_strchr(lex->token, '/') != NULL)
			return (0);
		if (ft_strchr(lex->token, '*') != NULL)
			return (1);
	}
	return (0);
}

/*
** Copy parameters from original to every node in linked list expand
*/
static void	fix_parameters(t_token *original, t_token *expand)
{
	t_token	*current;

	current = expand;
	while (current != NULL)
	{
		current->quote = original->quote;
		current = current->next;
	}
}

/*
** Takes a token lex and returns a wildcard matched linked list of tokens.
** CMD gets expanded to CMD->ARG->ARG. ARG gets expanded to ARG->ARG->ARG.
*/
static t_token	*expand_wildcard(t_token *lex, t_token **exp)
{
	DIR				*d;
	struct dirent	*de;
	int				t;

	if (!is_expandable(lex))
		return (NULL);
	*exp = NULL;
	d = opendir(".");
	if (d == NULL)
		return (NULL);
	de = readdir(d);
	while (de != NULL)
	{
		if (match_wildcard(de->d_name, lex->token))
		{
			if (de->d_name[0] != '.' || lex->token[0] == '.')
				ft_tokenadd_back(exp, ft_tokennew(ft_strdup(de->d_name), t));
				ft_tokenadd_back(exp, ft_tokennew(ft_strdup(de->d_name), t));
			t = ARG;
		}
		de = readdir(d);
	}
	closedir(d);
	fix_parameters(lex, *exp);
	return (*exp);
}

static int	wildcard_error(char *arg)
{
	ft_putstr_fd("minishell: no matches found: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

/*
** Expand every token in env
*/
int	expand_wildcard_tokens(t_env *env)
{
	t_token	*current;
	t_token	*next;
	t_token	*expand;

	current = env->token;
	while (current != NULL)
	{
		next = current->next;
		if (is_expandable(current))
		{
			if (expand_wildcard(current, &expand) == NULL)
				return (wildcard_error(current->token));
			ft_tokenadd_back(&expand, current->next);
			if (current == env->token)
				env->token = expand;
			else
			{
				current->prev->next = expand;
				expand->prev = current->prev;
			}
			ft_tokendelone(current);
		}
		current = next;
	}
	return (1);
}

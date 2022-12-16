/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:22:45 by abossel           #+#    #+#             */
/*   Updated: 2022/12/16 11:54:50 by abossel          ###   ########.fr       */
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
	if (lex->quote == 0)
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
static int	expand_wildcard(t_token *lex, t_token **exp)
{
	DIR				*d;
	struct dirent	*de;
	int				t;

	d = opendir(".");
	if (d == NULL)
		return (0);
	de = readdir(d);
	while (de != NULL)
	{
		if (ft_strncmp(de->d_name, "..", 3) && ft_strncmp(de->d_name, ".", 2)
			&& match_wildcard(de->d_name, lex->token))
		{
			if (de->d_name[0] != '.' || lex->token[0] == '.')
				ft_tokenadd_back(exp, ft_tokennew(ft_strdup(de->d_name), t));
			t = ARG;
		}
		de = readdir(d);
	}
	closedir(d);
	fix_parameters(lex, *exp);
	if (*exp != NULL)
		return (1);
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
		expand = NULL;
		next = current->next;
		if (is_expandable(current) && expand_wildcard(current, &expand))
		{
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

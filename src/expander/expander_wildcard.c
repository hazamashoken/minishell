/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:22:45 by abossel           #+#    #+#             */
/*   Updated: 2022/10/27 09:54:26 by abossel          ###   ########.fr       */
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
	if (lex->type == CMD || lex->type == ARG)
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
		current->piority = original->piority;
		current->quote = original->quote;
		current = current->next;
	}
}

/*
** Takes a token lex and returns a wildcard matched linked list of tokens.
** CMD gets expanded to CMD->ARG->ARG. ARG gets expanded to ARG->ARG->ARG.
*/
static t_token *expand_wildcard(t_token *lex)
{
	DIR 			*d;
	struct dirent	*de;
	t_token			*exp;
	int				type;

	if (!is_expandable(lex))
		return (NULL);
	exp = NULL;
	d = opendir(".");
	if (d == NULL)
		return (NULL);
	de = readdir(d);
	while (de != NULL)
	{
		if (match_wildcard(de->d_name, lex->token))
		{
			if (de->d_name[0] != '.' || lex->token[0] == '.')
				ft_tokenadd_back(&exp, ft_tokennew(ft_strdup(de->d_name), type));
			type = ARG;
		}
		de = readdir(d);
	}
	closedir(d);
	fix_parameters(lex, exp);
	return (exp);
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
			expand = expand_wildcard(current);
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
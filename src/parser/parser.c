/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:08 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/12 13:58:32 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	count_arg(t_token *token, int arg)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp->type != arg && tmp->next != NULL)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int	mallocers(char ****to_malloc, int size)
{
	*to_malloc = (char ***)malloc(sizeof(char **) * size);
	if (*to_malloc == NULL)
		return (EXIT_FAILURE);
	**to_malloc = NULL;
	return (EXIT_SUCCESS);
}

int	parse_file(t_env *env)
{
	t_token		*tmp;
	t_token		*new;
	int			i;

	i = 0;
	new = NULL;
	tmp = env->token;
	if (mallocers(&env->files, env->cmd_counts + 1))
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (tmp->type == FILEPATH)
			env->files[i] = (char **)nta_add_back((void **)env->files[i],
					ft_strdup(tmp->token));
		if (tmp->type != FILEPATH
			&& !(tmp->type >= TRUNC && tmp->type <= INPUT))
			ft_tokenadd_back(&new,
				ft_tokennew(ft_strdup(tmp->token), tmp->type));
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	env->files[++i] = NULL;
	printf("i %d\n", i);
	return (ft_tokenclear(&env->token), env->token = new, EXIT_SUCCESS);
}

int	parse_env(t_env *env)
{
	t_token		*tmp;
	char		**cmds;
	t_runner	r;

	tmp = env->token;
	r.j = 0;
	cmds = NULL;
	if (mallocers(&env->pipex_cmds, env->cmd_counts + 1))
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->prev == NULL)
		{
			if (tmp->prev != NULL)
			{
				env->pipex_cmds[r.j++] = cmds;
				tmp = tmp->next;
				if (tmp == NULL)
					break ;
			}
			cmds = (char **)malloc(sizeof(char *) * count_arg(tmp, PIPE));
		}
		cmds = (char **)nta_add_back((void **)cmds, ft_strdup(tmp->token));
		tmp = tmp->next;
	}
	printf("r.j %d\n", r.j);
	return (env->pipex_cmds[r.j++] = cmds,
		env->pipex_cmds[r.j] = NULL, EXIT_SUCCESS);
}

int	parser(t_env *env)
{
	printf("%d\n", env->cmd_counts);
	if (parse_file(env))
		return (EXIT_FAILURE);
	printf("=====\n");
	if (parse_env(env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

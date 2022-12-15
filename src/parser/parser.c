/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:01:08 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/14 17:12:24 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	count_arg(t_token *token, int arg)
// {
// 	t_token	*tmp;
// 	int		count;

// 	count = 0;
// 	tmp = token;
// 	while (tmp->type != arg && tmp->next != NULL)
// 	{
// 		tmp = tmp->next;
// 		count++;
// 	}
// 	return (count);
// }

// int	mallocers(char ****to_malloc, int size)
// {
// 	*to_malloc = (char ***)malloc(sizeof(char **) * size);
// 	if (*to_malloc == NULL)
// 		return (EXIT_FAILURE);
// 	**to_malloc = NULL;
// 	return (EXIT_SUCCESS);
// }

// int	parse_file(t_env *env)
// {
// 	t_token		*tmp;
// 	t_token		*new;
// 	int			i;

// 	i = 0;
// 	new = NULL;
// 	tmp = env->token;
// 	if (mallocers(&env->files, env->cmd_counts + 1))
// 		return (EXIT_FAILURE);
// 	while (tmp)
// 	{
// 		if (tmp->type == FILEPATH)
// 			env->files[i] = (char **)nta_add_back((void **)env->files[i],
// 					ft_strdup(tmp->token));
// 		if (tmp->type != FILEPATH
// 			&& !(tmp->type >= TRUNC && tmp->type <= INPUT))
// 			ft_tokenadd_back(&new,
// 				ft_tokennew(ft_strdup(tmp->token), tmp->type));
// 		if (tmp->type == PIPE)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	env->files[++i] = NULL;
// 	printf("i %d\n", i);
// 	return (ft_tokenclear(&env->token), env->token = new, EXIT_SUCCESS);
// }

// int	parse_env(t_env *env)
// {
// 	t_token		*tmp;
// 	char		**cmds;
// 	t_runner	r;

// 	tmp = env->token;
// 	r.j = 0;
// 	cmds = NULL;
// 	if (mallocers(&env->pipex_cmds, env->cmd_counts + 1))
// 		return (EXIT_FAILURE);
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE || tmp->prev == NULL)
// 		{
// 			if (tmp->prev != NULL)
// 			{
// 				env->pipex_cmds[r.j++] = cmds;
// 				tmp = tmp->next;
// 				if (tmp == NULL)
// 					break ;
// 			}
// 			cmds = (char **)malloc(sizeof(char *) * count_arg(tmp, PIPE));
// 		}
// 		cmds = (char **)nta_add_back((void **)cmds, ft_strdup(tmp->token));
// 		tmp = tmp->next;
// 	}
// 	printf("r.j %d\n", r.j);
// 	return (env->pipex_cmds[r.j++] = cmds,
// 		env->pipex_cmds[r.j] = NULL, EXIT_SUCCESS);
// }

// int	parser(t_env *env)
// {
// 	printf("%d\n", env->cmd_counts);
// 	if (parse_file(env))
// 		return (EXIT_FAILURE);
// 	printf("=====\n");
// 	if (parse_env(env))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

/*
 * parse command n from the t_env
 */
static char	**parse_command(t_env *env, int n)
{
	int		cmd_n;
	char	**cmd;
	t_token	*tok;

	cmd_n = 0;
	cmd = NULL;
	tok = env->token;
	while (tok != NULL)
	{
		if (tok->type == PIPE)
			cmd_n++;
		if (cmd_n == n && (tok->type == CMD || tok->type == ARG))
			cmd = (char **)nta_add_back((void **)cmd, ft_strdup(tok->token));
		tok = tok->next;
	}
	return (cmd);
}

/*
 * parse all io from command n in t_env
 */
static t_io	**parse_io(t_env *env, int n)
{
	int		cmd_n;
	t_token	*tok;
	t_io	**io;

	io = NULL;
	cmd_n = 0;
	tok = env->token;
	while (tok != NULL)
	{
		if (tok->type == PIPE)
			cmd_n++;
		if (cmd_n == n && (tok->type & (INPUT | FPATH)) == (INPUT | FPATH))
			io = add_file(io, tok->token, IO_READ, NULL);
		else if (cmd_n == n
			&& (tok->type & (HEREDOC | FPATH)) == (HEREDOC | FPATH))
			io = add_file(io, NULL, IO_HEREDOC, tok->token);
		else if (cmd_n == n && (tok->type & (TRUNC | FPATH)) == (TRUNC | FPATH))
			io = add_file(io, tok->token, IO_TRUNC, NULL);
		else if (cmd_n == n
			&& (tok->type & (APPEND | FPATH)) == (APPEND | FPATH))
			io = add_file(io, tok->token, IO_APPEND, NULL);
		tok = tok->next;
	}
	return (io);
}

/*
 * special case if pipe has io but no commands
 */
static char	**nocmd_special(void)
{
	char		**echo;

	echo = (char **)nta_add_back(NULL, (void *)ft_strdup("echo"));
	echo = (char **)nta_add_back((void **)echo, (void *)ft_strdup("-n"));
	return (echo);
}

static t_process	**build_pipex(t_env *env)
{
	t_process	**procs;
	t_io		**ios;
	char		**cmd;
	int			n;

	n = 0;
	procs = NULL;
	cmd = parse_command(env, n);
	ios = parse_io(env, n);
	if (cmd == NULL && ios != NULL)
		cmd = nocmd_special();
	while (cmd != NULL)
	{
		procs = add_proc(procs, cmd, environ);
		nta_free((void **)cmd);
		procs[n]->io = ios;
		n++;
		cmd = parse_command(env, n);
		ios = parse_io(env, n);
		if (cmd == NULL && ios != NULL)
			cmd = nocmd_special();
	}
	return (procs);
}

int	run_pipex(t_env *env)
{
	t_process	**procs;
	int			status;

	procs = build_pipex(env);
	if (procs == NULL)
		return (0);
	init_pipex(procs);
	status = args_exec(env, procs);
	free_pipex(procs);
	return (status);
}

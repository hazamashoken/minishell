/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:49:24 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/15 22:50:32 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	minishell_term(t_env *env)
{
	env->term = (t_term *)malloc(sizeof(t_term));
	if (env->term == NULL)
		return (-1);
	tcgetattr(STDIN_FILENO, &env->term->minishell);
	tcgetattr(STDIN_FILENO, &env->term->shell);
	env->term->minishell.c_lflag &= ~ECHOCTL;
	env->term->shell.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &env->term->minishell);
	return (0);
}

int	minishell_init(t_env *env)
{
	env->ret = 0;
	env->exit = 1;
	env->cmd_counts = 1;
	env->token = NULL;
	env->files = NULL;
	env->pipex_cmds = NULL;
	if (minishell_term(env) < 0)
	{
		perror("minishell");
		minishell_end(env);
		exit(EXIT_FAILURE);
	}
	env->errorchar = '\0';
	env->tmp_environ = environ;
	env->dup_environ = ft_split_dup(environ);
	environ = env->dup_environ;
	env->sigint.sa_handler = sig_handler;
	sigemptyset(&env->sigint.sa_mask);
	env->sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &env->sigint, NULL);
	env->sigquit.sa_handler = SIG_IGN;
	sigemptyset(&env->sigquit.sa_mask);
	env->sigquit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &env->sigquit, NULL);
	return (1);
}

void	minishell_end(t_env *env)
{
	rl_clear_history();
	environ = env->tmp_environ;
	ft_split_free(env->dup_environ);
	ft_tokenclear(&env->token);
	free(env->term);
}

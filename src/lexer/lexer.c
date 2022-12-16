/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:17:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/16 12:17:51 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_exit(t_env *env, char *input)
{
	ft_putstr_fd("minishell: parse error near `", 1);
	ft_putstr_fd(&env->errorchar, 1);
	ft_putstr_fd("\"\n", 1);
	ft_tokenclear(&env->token);
	free(input);
	env->ret = 258;
	return (1);
}

static int	error_exit2(t_env *env, char *input)
{
	ft_tokenclear(&env->token);
	free(input);
	env->ret = 258;
	return (1);
}

int	lexer(char *input, t_env *env)
{
	if (lexer_spliter(input, env))
		return (error_exit2(env, input));
	if (pre_sanitise(env))
		return (error_exit(env, input));
	expand_tilde(env);
	if (!expand_variable_tokens(env))
		return (error_exit2(env, input));
	if (quote_cleaner(env))
		return (error_exit(env, input));
	if (!expand_wildcard_tokens(env))
		return (error_exit2(env, input));
	if (type_check(env))
		return (error_exit(env, input));
	free(input);
	return (EXIT_SUCCESS);
}

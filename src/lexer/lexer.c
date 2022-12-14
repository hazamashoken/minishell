/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:17:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/13 22:05:02 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_exit(t_env *env, char *input)
{
	ft_putstr_fd("error\n", 1);
	ft_tokenclear(&env->token);
	free(input);
	return (1);
}

int	lexer(char *input, t_env *env)
{
	if (lexer_spliter(input, env))
		return (error_exit(env, input));
	if (pre_sanitise(env))
		return (error_exit(env, input));
	if (quote_cleaner(env))
		return (error_exit(env, input));
	//ft_tokenprint(env->token, -1, C_GREEN);
	if (!expand_variable_tokens(env))
		return (error_exit(env, input));
	if (!expand_wildcard_tokens(env))
		return (error_exit(env, input));
	//ft_tokenprint(env->token, -1, C_BLUE);
	if (type_check(env))
		return (error_exit(env, input));
	// bracket_cleaner(env);
	//ft_tokenprint(env->token, -1, C_YELLOW);
	free(input);
	return (EXIT_SUCCESS);
}

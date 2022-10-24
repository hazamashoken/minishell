/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:17:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/24 21:20:01 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

int	error_exit(t_env *env, char *input)
{
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
	type_check(env);
	free(input);
	return (EXIT_SUCCESS);
}

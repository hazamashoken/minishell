/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:17:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:37:28 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

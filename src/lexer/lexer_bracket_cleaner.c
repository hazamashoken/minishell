/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bracket_cleaner.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:45:32 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:54:53 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bracket_cleaner(t_env *env)
{
	t_token	*token;
	t_token	*tmp;

	token = env->token;
	while (token)
	{
		if (ft_strncmp(token->token, "(", 2) == 0)
		{
			if (token->next)
				tmp = token->next;
			ft_tokendel(token);
			token = tmp;
		}
		else
			token = token->next;
	}
}

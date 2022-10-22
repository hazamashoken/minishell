/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 11:49:07 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/22 14:26:51 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

void	ft_tokenprint(t_env *env)
{
	t_token	*token;

	token = env->token;
	while (token)
	{
		printf("<=========================================>\n");
		printf("<= Token\t:\t]%s[\t\t=>\n", token->token);
		printf("<= Type\t\t:\t]%d[\t\t=>\n", token->type);
		printf("<= Next Addr\t:\t]%-14p[=>\n", token->next);
		printf("<=========================================>\n");
		printf("\n");
		token = token->next;
	}
}

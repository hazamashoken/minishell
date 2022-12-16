/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tilde.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:20:27 by abossel           #+#    #+#             */
/*   Updated: 2022/12/16 10:23:52 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tilde(t_env *env)
{
	t_token	*tok;

	tok = env->token;
	while (tok != NULL)
	{
		if (ft_strncmp(tok->token, "~", 2) == 0)
		{
			free(tok->token);
			tok->token = ft_strdup("$HOME");
		}
		tok = tok->next;
	}
}

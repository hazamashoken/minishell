/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:39:28 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/24 20:46:11 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

static void	check_type(t_token *token)
{
	if (ft_strncmp(token->token, "", 1) == 0)
		token->type = EMPTY;
	else if (ft_strncmp(token->token, ">>", 2) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->token, ">", 1) == 0)
		token->type = TRUNC;
	else if (ft_strncmp(token->token, "<", 1) == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->token, "||", 2) == 0)
		token->type = OR;
	else if (ft_strncmp(token->token, "&&", 2) == 0)
		token->type = AND;
	else if (ft_strncmp(token->token, "|", 1) == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

void	type_check(t_env *env)
{
	t_token	*token;

	token = env->token;
	while (token)
	{
		check_type(token);
		token = token->next;
	}
}

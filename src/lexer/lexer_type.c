/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:39:28 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/11 23:39:16 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_type(t_token *token, int *cmd)
{
	if (ft_strncmp(token->token, "", 1) == 0)
		token->type = EMPTY;
	else if (ft_strncmp(token->token, "|", 1) == 0)
	{
		*cmd = 0;
		token->type = PIPE;
	}
	else if (ft_strncmp(token->token, ">>", 2) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->token, ">", 1) == 0)
		token->type = TRUNC;
	else if (ft_strncmp(token->token, "<", 1) == 0)
		token->type = INPUT;
	else if (token->prev != NULL
		&& token->prev->type >= TRUNC && token->prev->type <= INPUT)
		token->type = FILEPATH;
	else if (cmd == 0)
	{
		*cmd = 1;
		token->type = CMD;
	}
	else
		token->type = ARG;
	if (token->prev != NULL && (token->type == PIPE
			|| (token->prev->type >= TRUNC && token->prev->type <= INPUT
				&& token->type >= TRUNC && token->type <= INPUT)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// static void	check_type(t_token *token)
// {
// 	static int	piority;

// 	if (ft_strncmp(token->token, "", 1) == 0)
// 		token->type = EMPTY;
// 	else if (ft_strncmp(token->token, ">>", 2) == 0)
// 		token->type = APPEND;
// 	else if (ft_strncmp(token->token, ">", 1) == 0)
// 		token->type = TRUNC;
// 	else if (ft_strncmp(token->token, "<", 1) == 0)
// 		token->type = INPUT;
// 	else if (ft_strncmp(token->token, "||", 2) == 0)
// 		token->type = OR;
// 	else if (ft_strncmp(token->token, "&&", 2) == 0)
// 		token->type = AND;
// 	else if (ft_strncmp(token->token, "|", 1) == 0)
// 		token->type = PIPE;
// 	else if (ft_strncmp(token->token, "(", 1) == 0)
// 		piority++;
// 	else if (ft_strncmp(token->token, ")", 1) == 0)
// 		piority--;
// 	else if (token->prev == NULL || token->prev->type >= TRUNC)
// 		token->type = CMD;
// 	else
// 		token->type = ARG;
// 	token->piority = piority;
// }

int	type_check(t_env *env)
{
	t_token	*token;
	int		cmd_set;

	cmd_set = 0;
	token = NULL;
	printf("check\n");
	if (env->token)
		token = env->token;
	while (token)
	{
		if (check_type(token, &cmd_set))
			return (EXIT_FAILURE);
		printf("check2\n");
		token = token->next;
		printf("%p\n",token);
	}
	return (EXIT_SUCCESS);
}

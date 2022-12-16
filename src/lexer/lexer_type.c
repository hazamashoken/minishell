/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:39:28 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/16 13:59:03 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	return_check(t_env *env, t_token *token)
{
	if (token == NULL)
		;
	else if (token->prev == NULL && token->type == PIPE)
		return (env->errorchar = *token->token, EXIT_FAILURE);
	else if (token->type >= TRUNC && token->type <= HEREDOC
		&& token->next == NULL)
		return (env->errorchar = *token->token, EXIT_FAILURE);
	else if (token->prev == NULL)
		;
	else if (token->prev->type == PIPE && token->type == PIPE)
		return (env->errorchar = *token->token, EXIT_FAILURE);
	else if (token->prev->type >= TRUNC && token->prev->type <= HEREDOC
		&& token->type >= TRUNC && token->type <= HEREDOC)
		return (env->errorchar = *token->token, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_type(t_env *env, t_token *token, int *cmd)
{
	token->type = 0;
	if (token->quote != 0)
		return (token->type = ARG, EXIT_SUCCESS);
	if (ft_strncmp(token->token, "|", 1) == 0)
	{
		*cmd = 0;
		env->cmd_counts++;
		token->type = PIPE;
	}
	else if (ft_strncmp(token->token, ">>", 2) == 0)
		token->type |= APPEND;
	else if (ft_strncmp(token->token, "<<", 2) == 0)
		token->type |= HEREDOC;
	else if (ft_strncmp(token->token, ">", 1) == 0)
		token->type |= TRUNC;
	else if (ft_strncmp(token->token, "<", 1) == 0)
		token->type |= INPUT;
	else if (token->prev != NULL
		&& token->prev->type >= TRUNC && token->prev->type <= HEREDOC)
		token->type |= FPATH | token->prev->type;
	else if (cmd == 0)
		token->type = ++(*cmd) + 255;
	else
		token->type = ARG;
	return (return_check(env, token));
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
	if (env->token)
		token = env->token;
	while (token)
	{
		if (check_type(env, token, &cmd_set))
			return (EXIT_FAILURE);
		token = token->next;
	}
	return (EXIT_SUCCESS);
}

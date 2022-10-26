/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:37:44 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/24 20:43:33 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

int	main(void)
{
	char	*input;
	t_env	env;

	env.token = NULL;
	input = readline("\033[1;33mminishell >\033[0m ");
	if (input == NULL)
		return (1);
	if (lexer_spliter(input, &env))
		printf("Error\n");
	ft_tokenprint(env.token, -1, C_GREEN);
	if (pre_sanitise(&env))
		printf("Error\n");
	ft_tokenprint(env.token, -1, C_YELLOW);
	if (quote_cleaner(&env))
		printf("Error\n");
	ft_tokenprint(env.token, -1, C_BLUE);
	type_check(&env);
	ft_tokenprint(env.token, -1, C_YELLOW);
	ft_tokenclear(&env.token);
	free(input);
	return (EXIT_SUCCESS);
}
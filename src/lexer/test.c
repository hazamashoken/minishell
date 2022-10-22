/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:37:44 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/22 11:53:33 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

int	main(void)
{
	char	*input;
	t_env	env;

	env.token = NULL;
	input = readline("\033[1;33mminishell >\033[0m ");
	if (lexer(input, &env))
		printf("Error\n");
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:22 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 01:29:14 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cadet/minishell/includes/minishell.h"

// Use to handle ctrl+z, ctrl+c, ctrl+d
// signal() will redirect the SIG received
void	sig_handler(int signum)
{
	printf("sig_id: %d\n", signum);
}

int	main(void)
{
	const char	*input;

	printf("pid: %d\n", getpid());
	//signal(SIGINT, sig_handler);
	input = readline("\033[1;33mminishell >\033[0m ");
	if (lexer(input))
	 	error_exit(LEXER);
	// return (EXIT_FAILURE);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:22 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/27 10:01:01 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use to handle ctrl+z, ctrl+c, ctrl+d
// signal() will redirect the SIG received
void	sig_handler(int signum)
{
	printf("sig_id: %d\n", signum);
}
/*
int	main(void)
{
	const char	*input;

	printf("pid: %d\n", getpid());
	//signal(SIGINT, sig_handler);
	input = readline("\033[1;33mminishell >\033[0m ");
	if (lexer(input))
	 	error_exit(1);
	// return (EXIT_FAILURE);
	return (0);
}
*/
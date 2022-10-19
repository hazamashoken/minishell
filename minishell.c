/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:22 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/19 12:45:09 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use to handle ctrl+z, ctrl+c, ctrl+d
// signal() will redirect the SIG received
void	sig_handler(int signum)
{
	printf("sig_id: %d\n", signum);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	printf("pid: %d\n", getpid());
	signal(SIGINT, sig_handler);
	while (1)
	{
		usleep(100);
	}
	return (EXIT_FAILURE);
}

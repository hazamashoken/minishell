/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:49:22 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/19 12:56:56 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use to handle ctrl+z, ctrl+c, ctrl+d
// signal() will redirect the SIG received
void	sig_handler(int signum)
{
	printf("sig_id: %d\n", signum);
}

int	main(void)
{


	printf("pid: %d\n", getpid());
	signal(SIGINT, sig_handler);
	printf("%s\n", readline("minishell > "));
	return (EXIT_FAILURE);
}

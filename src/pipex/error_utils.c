/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:45:03 by abossel           #+#    #+#             */
/*   Updated: 2022/12/13 22:38:39 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
// #include "libft.h"
#include "minishell.h"

void	error_print(char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(127);
}

void	error_print2(char *message1, char *message2)
{
	ft_putstr_fd(message1, STDERR_FILENO);
	error_print(message2);
}

void	error_exit_pipex(void)
{
	perror(NULL);
	exit(EXIT_FAILURE);
}

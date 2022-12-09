/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:45:03 by abossel           #+#    #+#             */
/*   Updated: 2022/12/07 11:46:37 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "pipex.h"

void	error_print(char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	error_print2(char *message1, char *message2)
{
	ft_putstr_fd(message1, STDERR_FILENO);
	error_print(message2);
}

void	error_exit(void)
{
	perror(NULL);
	exit(EXIT_FAILURE);
}

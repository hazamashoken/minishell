/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:45:03 by abossel           #+#    #+#             */
/*   Updated: 2022/12/11 16:59:56 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
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

void	error_exit_pipex(void)
{
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}

int	open_files(char *input, char *output, int *fd, int append)
{
	fd[0] = open(input, O_RDONLY);
	fd[1] = -1;
	if (fd[0] == -1)
		return (0);
	if (!append)
		fd[1] = open(output, O_CREAT | O_WRONLY | O_CLOEXEC | O_TRUNC, 0644);
	else
		fd[1] = open(output, O_CREAT | O_WRONLY | O_CLOEXEC | O_APPEND, 0644);
	if (fd[1] == -1)
	{
		close(fd[0]);
		fd[0] = -1;
		return (0);
	}
	return (1);
}

void	close_files(int	*fd)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	fd[0] = -1;
	fd[1] = -1;
}

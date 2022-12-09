/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:27:47 by abossel           #+#    #+#             */
/*   Updated: 2022/12/08 16:55:34 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"

static int	open_file(t_io *io)
{
	if (io->type == IO_READ)
		return (open(io->filename, O_RDONLY));
	else if (io->type == IO_HEREDOC)
	{
		io->filename = read_here_doc(io->limiter);
		return (open(io->filename, O_RDONLY));
	}
	else if (io->type == IO_APPEND)
		return (open(io->filename,
				O_CREAT | O_WRONLY | O_CLOEXEC | O_APPEND, 0644));
	else if (io->type == IO_TRUNC)
		return (open(io->filename,
				O_CREAT | O_WRONLY | O_CLOEXEC | O_TRUNC, 0644));
	return (-1);
}

t_io	**add_file(t_io **ios, char *filename, int type, char *limiter)
{
	t_io	*io;

	io = malloc(sizeof(t_io));
	if (io == NULL)
		return (NULL);
	io->filename = NULL;
	io->limiter = NULL;
	io->type = type;
	io->fd = -1;
	if (filename != NULL)
		io->filename = ft_strdup(filename);
	if (limiter != NULL)
		io->limiter = ft_strdup(limiter);
	return ((t_io **)nta_add_back((void **)ios, (void *)io));
}

int	open_files(t_io **ios)
{
	int	size;
	int	i;

	if (ios == NULL)
		return (0);
	size = nta_size((void **)ios);
	i = 0;
	while (i < size)
	{
		ios[i]->fd = open_file(ios[i]);
		if (ios[i]->fd == -1)
			error_exit();
		i++;
	}
	return (1);
}

void	close_files(t_io **ios)
{
	int	size;
	int	i;

	if (ios == NULL)
		return ;
	size = nta_size((void **)ios);
	i = 0;
	while (i < size)
	{
		if (ios[i]->fd != -1)
		{
			close(ios[i]->fd);
			ios[i]->fd = -1;
			if (ios[i]->type == IO_HEREDOC)
				unlink(ios[i]->filename);
		}
		i++;
	}
}

void	free_files(t_io **ios)
{
	int	size;
	int	i;

	if (ios == NULL)
		return ;
	close_files(ios);
	size = nta_size((void **)ios);
	i = 0;
	while (i < size)
	{
		if (ios[i]->filename != NULL)
			free(ios[i]->filename);
		if (ios[i]->limiter != NULL)
			free(ios[i]->limiter);
		i++;
	}
	nta_free((void **)ios);
}

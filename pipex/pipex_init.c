/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:33:57 by abossel           #+#    #+#             */
/*   Updated: 2022/12/08 16:38:51 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "pipex.h"

static int	**init_pipes(t_process **procs)
{
	int	**pipes;
	int	num_pipes;
	int	num_procs;
	int	i;

	num_procs = nta_size((void **)procs);
	num_pipes = num_procs - 1;
	pipes = make_pipes(num_pipes);
	if (pipes != NULL)
	{
		i = 0;
		while (i < num_procs)
		{
			procs[i]->pipes = pipes;
			if (i != 0)
				procs[i]->parent = pipes[i - 1];
			if (i != num_procs - 1)
				procs[i]->child = pipes[i];
			i++;
		}
	}
	return (pipes);
}

void	set_file_io(t_process *proc)
{
	int	i;

	if (proc == NULL || proc->io == NULL)
		return ;
	i = 0;
	while (proc->io[i] != NULL)
	{
		if ((proc->io[i]->type == IO_READ || proc->io[i]->type == IO_HEREDOC)
			&& proc->io[i]->fd != -1)
		{
			proc->parent = proc->fileio;
			proc->fileio[0] = proc->io[i]->fd;
		}
		if ((proc->io[i]->type == IO_TRUNC || proc->io[i]->type == IO_APPEND)
			&& proc->io[i]->fd != -1)
		{
			proc->child = proc->fileio;
			proc->fileio[1] = proc->io[i]->fd;
		}
		i++;
	}
}

void	*free_pipex(t_process **procs)
{
	if (procs == NULL)
		return (NULL);
	close_pipes(procs[0]->pipes);
	free_pipes(procs[0]->pipes);
	free_procs(procs);
	return (NULL);
}

int	init_pipex(t_process **procs)
{
	int	**pipes;

	pipes = init_pipes(procs);
	if (pipes == NULL)
		return (0);
	return (1);
}

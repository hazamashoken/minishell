/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:33:57 by abossel           #+#    #+#             */
/*   Updated: 2022/10/08 16:44:43 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "pipex.h"

static t_process	**init_procs(int argc, char **argv, char **envp)
{
	t_process	**procs;
	int			num_procs;
	char		**argv2;
	int			i;

	num_procs = argc - 3;
	procs = make_procs(num_procs);
	if (procs != NULL)
	{
		i = 0;
		argv2 = argv + 2;
		while (i < num_procs)
		{
			set_proc_args(procs[i], argv2[i], envp);
			i++;
		}
	}
	return (procs);
}

static int	**init_pipes(int argc, t_process **procs)
{
	int	**pipes;
	int	num_pipes;
	int	num_procs;
	int	i;

	num_pipes = argc - 4;
	num_procs = argc - 3;
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

static int	init_files(int argc, char **argv, t_process **procs, int append)
{
	int	fd[2];
	int	i;

	if (open_files(argv[1], argv[argc - 1], fd, append))
	{
		procs[0]->file[0] = fd[0];
		procs[0]->file[1] = fd[1];
		procs[0]->parent = procs[0]->file;
		i = 0;
		while (procs[i] != NULL)
			i++;
		i--;
		procs[i]->file[0] = fd[0];
		procs[i]->file[1] = fd[1];
		procs[i]->child = procs[i]->file;
		return (1);
	}
	return (0);
}

void	*free_pipex(t_process **procs)
{
	if (procs == NULL)
		return (NULL);
	close_files(procs[0]->file);
	close_pipes(procs[0]->pipes);
	free_pipes(procs[0]->pipes);
	free_procs(procs);
	return (NULL);
}

t_process	**init_pipex(int argc, char **argv, char **envp)
{
	t_process	**procs;

	procs = init_procs(argc, argv, envp);
	if (procs != NULL)
		if (init_pipes(argc, procs) != NULL)
			if (init_files(argc, argv, procs, 0) != 0)
				return (procs);
	free_pipex(procs);
	return (NULL);
}

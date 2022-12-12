/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_factory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:19:51 by abossel           #+#    #+#             */
/*   Updated: 2022/12/08 17:01:34 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "pipex.h"

static void	set_proc_clean(t_process *proc)
{
	proc->pid = -1;
	proc->status = 0;
	proc->fileio[0] = 0;
	proc->fileio[1] = 1;
	proc->parent = proc->fileio;
	proc->child = proc->fileio;
	proc->pipes = NULL;
	proc->argc = 0;
	proc->argv = NULL;
	proc->envp = NULL;
	proc->io = NULL;
}

void	free_procs(t_process **procs)
{
	int	i;

	if (procs != NULL)
	{
		i = 0;
		while (procs[i] != NULL)
		{
			ft_split_free(procs[i]->argv);
			ft_split_free(procs[i]->envp);
			close_files(procs[i]->io);
			free_files(procs[i]->io);
			i++;
		}
		nta_free((void **)procs);
	}
}

t_process	**add_proc(t_process **procs, char **argv, char **envp)
{
	t_process	*proc;
	char		*path;

	proc = malloc(sizeof(t_process));
	if (proc == NULL)
		return (0);
	set_proc_clean(proc);
	proc->argc = ft_split_size(argv);
	proc->argv = ft_split_dup(argv);
	path = get_pathname(proc->argv[0], envp);
	free(proc->argv[0]);
	proc->argv[0] = path;
	proc->envp = ft_split_dup(envp);
	return ((t_process **)nta_add_back((void **)procs, (void *)proc));
}

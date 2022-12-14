/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_factory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:19:51 by abossel           #+#    #+#             */
/*   Updated: 2022/12/13 19:01:54 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include "libft.h"
#include "minishell.h"

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
	proc->path = NULL;
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
			if (procs[i]->path != NULL)
				free(procs[i]->path);
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

	proc = malloc(sizeof(t_process));
	if (proc == NULL)
		return (0);
	set_proc_clean(proc);
	proc->argc = ft_split_size(argv);
	proc->argv = ft_split_dup(argv);
	proc->path = get_pathname(argv[0], envp);
	proc->envp = ft_split_dup(envp);
	return ((t_process **)nta_add_back((void **)procs, (void *)proc));
}

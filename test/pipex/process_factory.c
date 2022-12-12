/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_factory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:19:51 by abossel           #+#    #+#             */
/*   Updated: 2022/10/07 14:56:57 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "pipex.h"

static void	set_proc_clean(t_process *proc)
{
	proc->pid = -1;
	proc->file[0] = -1;
	proc->file[1] = -1;
	proc->parent = NULL;
	proc->child = NULL;
	proc->pipes = NULL;
	proc->argc = -1;
	proc->argv = NULL;
	proc->envp = NULL;
}

void	set_proc_args(t_process *proc, char *command, char **envp)
{
	char	**args;
	char	*pathname;

	args = ft_split(command, ' ');
	if (args != NULL)
	{
		pathname = get_pathname(args[0], envp);
		if (pathname != NULL)
		{
			free(args[0]);
			args[0] = pathname;
		}
		proc->argc = ft_split_size(args);
		proc->argv = args;
		proc->envp = envp;
	}
}

void	*free_procs(t_process **procs)
{
	int	i;

	if (procs != NULL)
	{
		i = 0;
		while (procs[i] != NULL)
		{
			if (procs[i]->argv != NULL)
				ft_split_free(procs[i]->argv);
			free(procs[i]);
			i++;
		}
		free(procs);
	}
	return (NULL);
}

t_process	**make_procs(int n)
{
	t_process	**procs;
	int			i;

	if (n < 1)
		return (NULL);
	procs = malloc(sizeof(t_process *) * (n + 1));
	if (procs == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		procs[i] = malloc(sizeof(t_process));
		if (procs[i] == NULL)
			return (free_procs(procs));
		set_proc_clean(procs[i]);
		i++;
	}
	procs[n] = NULL;
	return (procs);
}

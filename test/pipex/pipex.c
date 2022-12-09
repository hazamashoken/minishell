/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:26:11 by abossel           #+#    #+#             */
/*   Updated: 2022/12/07 13:35:51 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"

static void	print_proc(t_process *proc)
{
	int	i;

	ft_printf("pid: %d\n", proc->pid);
	ft_printf("files: %d, %d\n", proc->fileio[0], proc->fileio[1]);
	ft_printf("parent: %d, %d\n", proc->parent[0], proc->parent[1]);
	ft_printf("child: %d, %d\n", proc->child[0], proc->child[1]);
	ft_printf("arg: %d, %s\n", proc->argc, proc->argv[0]);
	if (proc->io != NULL)
	{
		i = 0;
		while (proc->io[i] != NULL)
		{
			ft_printf("file: %s\n", proc->io[i]->filename);
			i++;
		}
	}
	ft_printf("\n");
}

static pid_t	fork_exec(t_process *proc)
{
	pid_t	pid;

	print_proc(proc);
	pid = fork();
	if (pid == 0)
	{
		if (proc->parent[0] != 0)
			dup2(proc->parent[0], 0);
		if (proc->child[1] != 1)
			dup2(proc->child[1], 1);
		close_pipes(proc->pipes);
		execve(proc->argv[0], proc->argv, proc->envp);
		error_print2("error: command not found: ", proc->argv[0]);
	}
	else if (pid == -1)
		error_exit();
	proc->pid = pid;
	return (pid);
}

static int	args_exec(t_process **procs)
{
	int	status;
	int	size;
	int	i;

	size = 0;
	while (procs[size] != NULL)
		size++;
	i = 0;
	while (i < size)
	{
		open_files(procs[i]->io);
		set_file_io(procs[i]);
		fork_exec(procs[i]);
		i++;
	}
	close_pipes(procs[0]->pipes);
	i = 0;
	while (i < size)
	{
		waitpid(procs[i]->pid, &status, 0);
		procs[i]->status = WEXITSTATUS(status);
		close_files(procs[i]->io);
		i++;
	}
	return (procs[size - 1]->status);
}

int	main(int argc, char **argv, char **envp)
{
	char		*argv1[5] = { "cat", NULL };
	char		*argv2[5] = { "cat", NULL };
	char		*argv3[5] = { "cat", NULL };
	t_process	**procs;
	int			status;

	if (argc || argv)
		;
	procs = NULL;
	procs = add_proc(procs, argv1, envp);
	procs[0]->io = add_file(procs[0]->io, "0abc.txt", IO_READ, NULL);
	procs[0]->io = add_file(procs[0]->io, "0def.txt", IO_READ, NULL);
	procs[0]->io = add_file(procs[0]->io, "0out1.txt", IO_TRUNC, NULL);

	procs = add_proc(procs, argv2, envp);
	procs[1]->io = add_file(procs[1]->io, "0xyz.txt", IO_READ, NULL);
	procs[1]->io = add_file(procs[1]->io, NULL, IO_HEREDOC, "123");

	procs = add_proc(procs, argv3, envp);
	procs[2]->io = add_file(procs[2]->io, "0out2.txt", IO_TRUNC, NULL);
	procs[2]->io = add_file(procs[2]->io, "0out3.txt", IO_APPEND, NULL);

	init_pipex(procs);
	status = args_exec(procs);
	free_pipex(procs);
	return (status);
}

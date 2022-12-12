/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:26:11 by abossel           #+#    #+#             */
/*   Updated: 2022/10/09 01:29:36 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"

static pid_t	fork_exec(t_process *proc)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(proc->parent[0], 0);
		dup2(proc->child[1], 1);
		close_pipes(proc->pipes);
		execve(proc->argv[0], proc->argv, proc->envp);
		ft_putstr_fd("error: command not found: ", STDERR_FILENO);
		error_print(proc->argv[0]);
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
		fork_exec(procs[i]);
		i++;
	}
	close_pipes(procs[0]->pipes);
	i = 0;
	while (i < size)
	{
		waitpid(procs[i]->pid, &status, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}

/*
static void	print_proc(t_process *proc)
{
	ft_printf("pid: %d\n", proc->pid);
	ft_printf("files: %d, %d\n", proc->file[0], proc->file[1]);
	ft_printf("parent: %d, %d\n", proc->parent[0], proc->parent[1]);
	ft_printf("child: %d, %d\n", proc->child[0], proc->child[1]);
	ft_printf("arg: %d, %s\n", proc->argc, proc->argv[0]);
}
*/

int	main(int argc, char **argv, char **envp)
{
	t_process	**procs;
	char		**argv_heredoc;
	int			status;

	if (argc < 5)
		error_print("usage: pipex file command command [command...] file\n"
			"       pipex here_doc limiter cmd cmd [cmd...] file");
	argv_heredoc = NULL;
	if (argc >= 6 && ft_strncmp("here_doc", argv[1], 9) == 0)
	{
		argv_heredoc = make_argv_heredoc(argv);
		procs = init_pipex(argc - 1, argv_heredoc + 1, envp);
	}
	else
		procs = init_pipex(argc, argv, envp);
	if (procs == NULL)
		error_exit();
	status = args_exec(procs);
	if (argv_heredoc != NULL)
	{
		unlink(argv_heredoc[2]);
		ft_split_free(argv_heredoc);
	}
	free_pipex(procs);
	exit(status);
}

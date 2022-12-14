/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:26:11 by abossel           #+#    #+#             */
/*   Updated: 2022/12/14 21:28:00 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// #include "libft.h"
#include "minishell.h"

// static void	print_proc(t_process *proc)
// {
// 	int	i;

// 	printf("pid: %d\n", proc->pid);
// 	printf("files: %d, %d\n", proc->fileio[0], proc->fileio[1]);
// 	printf("parent: %d, %d\n", proc->parent[0], proc->parent[1]);
// 	printf("child: %d, %d\n", proc->child[0], proc->child[1]);
// 	printf("arg: %d, %s\n", proc->argc, proc->argv[0]);
// 	printf("path: %s\n", proc->path);
// 	if (proc->io != NULL)
// 	{
// 		i = 0;
// 		while (proc->io[i] != NULL)
// 		{
// 			printf("file: %s\n", proc->io[i]->filename);
// 			i++;
// 		}
// 	}
// 	printf("\n");
// }

static int	run_builtin_outside(t_env *env, t_process *proc)
{
	proc->status = -1;
	if (ft_strncmp(proc->argv[0], "cd", 3) == 0)
		proc->status = mini_cd(&proc->argv[1]);
	else if (ft_strncmp(proc->argv[0], "export", 7) == 0)
		proc->status = mini_export(env, proc->argv);
	else if (ft_strncmp(proc->argv[0], "unset", 6) == 0)
		proc->status = mini_unset(proc->argv);
	else if (ft_strncmp(proc->argv[0], "exit", 5) == 0)
		proc->status = mini_exit(env, proc->argv);
	return (proc->status);
}

static int	run_builtin_inside(t_process *proc)
{
	proc->status = -1;
	if (ft_strncmp(proc->argv[0], "echo", 5) == 0)
		proc->status = mini_echo(proc->argv);
	else if (ft_strncmp(proc->argv[0], "pwd", 4) == 0)
		proc->status = mini_pwd();
	else if (ft_strncmp(proc->argv[0], "env", 4) == 0)
		proc->status = mini_env();
	return (proc->status);
}

static pid_t	fork_exec(t_process *proc)
{
	proc->pid = fork();
	if (proc->pid == 0)
	{
		if (proc->parent[0] != 0)
			dup2(proc->parent[0], 0);
		if (proc->child[1] != 1)
			dup2(proc->child[1], 1);
		close_pipes(proc->pipes);
		if (run_builtin_inside(proc) != -1)
			exit(proc->status);
		execve(proc->path, proc->argv, proc->envp);
		error_print2("error: command not found: ", proc->argv[0]);
	}
	else if (proc->pid == -1)
		error_exit_pipex();
	return (proc->pid);
}

int	args_exec(t_env *env, t_process **procs)
{
	int	status;
	int	i;

	i = 0;
	while (procs[i] != NULL)
	{
		open_files(procs[i]->io);
		set_file_io(procs[i]);
		if (run_builtin_outside(env, procs[i]) == -1)
			fork_exec(procs[i]);
		i++;
	}
	close_pipes(procs[0]->pipes);
	i = 0;
	while (procs[i] != NULL)
	{
		if (procs[i]->pid != -1)
		{
			waitpid(procs[i]->pid, &status, 0);
			procs[i]->status = WEXITSTATUS(status);
		}
		close_files(procs[i]->io);
		i++;
	}
	return (procs[nta_size((void **)procs) - 1]->status);
}

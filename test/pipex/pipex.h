/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:04:13 by abossel           #+#    #+#             */
/*   Updated: 2022/10/08 23:53:54 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_process
{
	int		pid;
	int		file[2];
	int		*parent;
	int		*child;
	int		**pipes;
	int		argc;
	char	**argv;
	char	**envp;
}	t_process;

void		*free_pipes(int **pipes);
int			**close_pipes(int **pipes);
int			**make_pipes(int n);
char		*get_pathname(char *cmd, char **envp);
void		error_print(char *message);
void		error_exit(void);
int			open_files(char *input, char *output, int *fd, int here_doc);
void		close_files(int	*fd);
void		set_proc_args(t_process *proc, char *command, char **envp);
void		*free_procs(t_process **proc);
t_process	**make_procs(int n);
void		*free_pipex(t_process **procs);
t_process	**init_pipex(int argc, char **argv, char **envp);
char		**make_argv_heredoc(char **argv);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:45:53 by abossel           #+#    #+#             */
/*   Updated: 2022/10/08 23:56:25 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"

static void	read_until_limiter(int fd_input, int fd_output, char *limiter)
{
	char	*line;
	int		size;

	size = ft_strlen(limiter);
	line = get_next_line(fd_input);
	while (line != NULL)
	{
		if (ft_strncmp(limiter, line, size) == 0)
		{
			free(line);
			line = NULL;
		}
		else
		{
			ft_putstr_fd(line, fd_output);
			free(line);
			line = get_next_line(fd_input);
		}
	}
}

static char	*read_here_doc(char *limiter)
{
	char	pathname[100];
	char	*number;
	int		fd;
	int		i;

	i = 0;
	while (i < 1000)
	{
		number = ft_itoa(i);
		ft_strlcpy(pathname, "/tmp/pipex_", 100);
		ft_strlcat(pathname, number, 100);
		free(number);
		if (access(pathname, F_OK) == -1)
		{
			fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0600);
			if (fd != -1)
			{
				read_until_limiter(STDIN_FILENO, fd, limiter);
				close(fd);
				return (ft_strdup(pathname));
			}
		}
		i++;
	}
	return (NULL);
}

char	**make_argv_heredoc(char **argv)
{
	char	**argv_heredoc;
	char	*arg2;

	argv_heredoc = ft_split_dup(argv);
	if (argv_heredoc != NULL)
	{
		arg2 = read_here_doc(argv[2]);
		if (arg2 == NULL)
		{
			ft_split_free(argv_heredoc);
			return (NULL);
		}
		free(argv_heredoc[2]);
		argv_heredoc[2] = arg2;
	}
	return (argv_heredoc);
}

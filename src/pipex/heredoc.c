/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:45:53 by abossel           #+#    #+#             */
/*   Updated: 2022/12/13 19:01:14 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
// #include "libft.h"
#include "minishell.h"

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

char	*read_here_doc(char *limiter)
{
	char	pathname[20];
	char	*number;
	int		fd;
	int		i;

	i = 1;
	while (i < 1000)
	{
		number = ft_itoa(i);
		ft_strlcpy(pathname, "/tmp/pipex", 20);
		ft_strlcat(pathname, number, 20);
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

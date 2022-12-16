/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_factory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:02:32 by abossel           #+#    #+#             */
/*   Updated: 2022/10/06 16:43:15 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"

void	*free_pipes(int **pipes)
{
	int	i;

	if (pipes != NULL)
	{
		i = 0;
		while (pipes[i] != NULL)
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
	return (NULL);
}

int	**close_pipes(int **pipes)
{
	int	i;

	if (pipes != NULL)
	{
		i = 0;
		while (pipes[i] != NULL)
		{
			if (pipes[i][0] != -1)
				close(pipes[i][0]);
			if (pipes[i][1] != -1)
				close(pipes[i][1]);
			i++;
		}
	}
	return (pipes);
}

int	**make_pipes(int n)
{
	int	**pipes;
	int	i;

	if (n < 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * (n + 1));
	if (pipes == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
			return (free_pipes(pipes));
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		if (pipe(pipes[i]) != 0)
			return (free_pipes(close_pipes(pipes)));
		i++;
	}
	pipes[n] = NULL;
	return (pipes);
}

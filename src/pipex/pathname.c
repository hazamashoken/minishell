/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 02:39:47 by abossel           #+#    #+#             */
/*   Updated: 2022/12/13 20:15:35 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "minishell.h"

static char	**get_path(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (ft_split((*envp) + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	*get_pathname(char *cmd, char **envp)
{
	char	pathname[PATH_MAX];
	char	**path;
	int		i;

	if (access(cmd, X_OK) != -1)
		return (ft_strdup(cmd));
	i = 0;
	path = get_path(envp);
	while (path != NULL && path[i] != NULL)
	{
		ft_strlcpy(pathname, path[i], PATH_MAX);
		ft_strlcat(pathname, "/", PATH_MAX);
		ft_strlcat(pathname, cmd, PATH_MAX);
		if (access(pathname, X_OK) != -1)
			break ;
		ft_strlcpy(pathname, cmd, PATH_MAX);
		i++;
	}
	ft_split_free(path);
	return (ft_strdup(pathname));
}

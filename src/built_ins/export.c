/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:40:10 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/14 14:22:09 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_env(char *args)
{
	int	i;

	i = -1;
	while (environ[++i])
	{
		if (ft_strlcmpchr(environ[i], args, '=')
			== ft_strunspn(environ[i], "=") + 1
			&& ft_strunspn(environ[i], "=")
			== ft_strunspn(args, "="))
		{
			free(environ[i]);
			environ[i] = ft_strdup(args);
			return ;
		}
	}
	environ = ft_split_addback(environ, args);
}

int	mini_export(char **args)
{
	int		i;

	i = 0;
	while (args[++i])
		reset_env(args[i]);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:40:10 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/14 21:27:15 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	**add_back(char *args)
{
	environ = ft_split_addback(environ, args);
	return (environ);
}
*/

void	reset_env(t_env *env, char *args)
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
	env->dup_environ = ft_split_addback(env->dup_environ, args);
	environ = env->dup_environ;
}

int	mini_export(t_env *env, char **args)
{
	int		i;

	i = 0;
	while (args[++i])
		reset_env(env, args[i]);
	return (EXIT_SUCCESS);
}

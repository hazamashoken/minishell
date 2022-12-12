/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:40:10 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:54:17 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *env)
{
	char	**dup;

	dup = ft_split_dup(environ);
	ft_split_free(environ);
	environ = dup;
	environ = ft_split_addback(dup, env);
	dup = environ;

}

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
	add_env(args);
}

void	mini_export(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
		reset_env(args[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:25:56 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:54:36 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_is_env(char *args, char *env)
{
	int	i;

	i = 0;
	while (args[i] == env[i])
		i++;
	if (args[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

int	unset_env(char *args)
{
	int	i;

	i = -1;
	if (ft_strchr(args, '='))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd(": invalid parameter name\n", 2);
		return (1);
	}
	while (environ[++i])
	{
		if (arg_is_env(args, environ[i]))
		{
			free(environ[i]);
			environ[i] = ft_strdup("\0");
			return (0);
		}
	}
	return (0);
}

void	mini_unset(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		unset_env(args[i]);
}

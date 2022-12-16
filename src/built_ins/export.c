/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:40:10 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/15 22:26:38 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_env *env, char *args)
{
	env->dup_environ = ft_split_addback(env->dup_environ, args);
	environ = env->dup_environ;
}

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
	if (ft_strchr(args, '='))
		add_back(env, args);
}

void	print_free(char **sort)
{
	int	i;

	i = -1;
	while (sort[++i])
	{
		printf("%s\n", sort[i]);
		free(sort[i]);
	}
	free(sort);
}

void	print_sorted_env(void)
{
	char	**sort;
	char	*buf;
	int		i;
	int		j;

	i = 0;
	sort = ft_split_dup(environ);
	while (i < args_len(environ))
	{
		j = i + 1;
		while (j < args_len(environ))
		{
			if (ft_strcmp(sort[i], sort[j]) > 0)
			{
				buf = sort[i];
				sort[i] = sort[j];
				sort[j] = buf;
			}
			j++;
		}
		i++;
	}
	print_free(sort);
}

int	mini_export(t_env *env, char **args)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
		print_sorted_env();
	else
		while (args[++i])
			reset_env(env, args[i]);
	return (EXIT_SUCCESS);
}

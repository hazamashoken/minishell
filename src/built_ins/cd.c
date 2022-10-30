/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:16:07 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/27 21:34:17 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

void	mini_cd(t_env *env, char **args)
{
	char	*error;

	if (args_len(args) > 2)
		error_put(env, "cd: too many arguments", NULL, 1);
	else if (chdir(args[0]) == -1)
	{
		error = strerror(errno);
		write(1, "cd: ", 4);
		ft_putstr_fd(error, 1);
		write(1, ": ", 2);
		ft_putstr_fd(args[0], 1);
		write(1, "\n", 1);
		free(error);
		printf("errno: %d\n", errno);
		env->ret = 1;
	}
}

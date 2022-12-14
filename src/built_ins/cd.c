/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:16:07 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/13 16:17:02 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(t_env *env, char **args)
{
	char	*error;

	if (env)
		;
	if (chdir(args[0]) == -1)
	{
		error = strerror(errno);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		//printf("errno: %d\n", errno);
		//env->ret = 1;
		return (1);
	}
	return (0);
}

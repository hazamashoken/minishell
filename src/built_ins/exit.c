/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:38:36 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:54:14 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: WIP
void	mini_exit(t_env *env, char **args)
{
	if (args_len(args) > 0)
	{
		env->ret = ft_atoi(args[0]);
	}
	else
		env->ret = 0;
	ft_putstr_fd("exit", 1);
	env->exit = 1;
}

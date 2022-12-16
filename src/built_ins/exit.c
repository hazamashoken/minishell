/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:38:36 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/15 13:20:59 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_exit(t_env *env, char **args)
{
	env->exit = 0;
	if (args_len(args) > 1)
		return (ft_atoi(args[1]));
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:24:47 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:53:59 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_put( t_env *env, char *str, char *args, int sig)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (args != NULL)
		ft_putstr_fd(args, STDERR_FILENO);
	write(1, "\n", 1);
	env->ret = sig;
}

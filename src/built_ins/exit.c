/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:38:36 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/14 13:52:45 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_exit(char **args)
{
	ft_putstr_fd("exit", 1);
	if (args_len(args) > 0)
		return (ft_atoi(args[0]));
	else
		return (0);
}

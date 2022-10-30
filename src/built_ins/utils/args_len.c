/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:37:59 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/27 15:25:02 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../cadet/minishell/includes/minishell.h"

int	args_len(char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

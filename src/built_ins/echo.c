/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:59:27 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:54:04 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	if (args_len(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
		{
			nl = 1;
			i++;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
		}
	}
	if (nl == 0)
		write(1, "\n", 1);
	return (0);
}

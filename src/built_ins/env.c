/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:26:16 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/15 12:51:03 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(void)
{
	int	i;

	i = -1;
	while (environ[++i])
	{
		if (ft_strncmp(environ[i], "_=", 2) != 0)
			printf("%s\n", environ[i]);
	}
	printf("_=%s\n", getenv("_"));
	return (EXIT_SUCCESS);
}

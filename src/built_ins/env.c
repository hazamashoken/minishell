/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:26:16 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/14 13:21:50 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(void)
{
	int	i;

	i = -1;
	while (environ[++i])
	{
		if (environ[i][0] != '_'
			&& environ[i][0] != '\0' && environ[i][1] != '=')
			printf("%s\n", environ[i]);
	}
	printf("_=%s\n", getenv("_"));
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:26:16 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/29 20:50:03 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../cadet/minishell/includes/minishell.h"

void	mini_env(void)
{
	int	i;

	i = -1;
	while (environ[++i])
	{
		if (environ[i][0] != '_' && environ[i][0] != '\0')
			printf("%s\n", environ[i]);
	}
	printf("_=%s\n", getenv("_"));
}

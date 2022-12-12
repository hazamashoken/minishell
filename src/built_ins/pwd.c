/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:12:26 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:54:22 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(t_env *env)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		env->ret = 1;
	printf("%s\n", buf);
	free(buf);
}

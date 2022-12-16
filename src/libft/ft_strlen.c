/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 10:23:15 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/09 11:31:28 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*(unsigned char *)(s + len) != '\0')
		len++;
	return (len);
}

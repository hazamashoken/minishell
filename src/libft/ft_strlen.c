/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 10:23:15 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:40:22 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (*(unsigned char *)(s + len) != '\0')
		len++;
	return (len);
}

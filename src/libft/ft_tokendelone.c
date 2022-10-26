/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokendelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:44:56 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:39:22 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tokendelone(t_token *token)
{
	if (token != NULL)
	{
		free(token->token);
		free(token);
	}
}

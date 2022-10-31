/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 11:49:07 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/31 19:12:40 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tokenprint(t_token *token, int mode, char *color)
{
	t_token	*tmp;

	tmp = token;
	//printf("%d\n", mode);
	while (tmp && (mode-- || mode == -1))
	{
		printf("%s<================================================>%s\n", color,C_RESET);
		printf("%s<= Token\t:\t]%s[\t\t\t=>%s\n", color, tmp->token, C_RESET);
		printf("%s<= Type\t\t:\t]%d[\t\t\t=>%s\n", color, tmp->type,C_RESET);
		printf("%s<= Quote type\t:\t]%d[\t\t\t=>%s\n", color, tmp->quote,C_RESET);
		printf("%s<= Priority\t:\t]%d[\t\t\t=>%s\n", color, tmp->piority,C_RESET);
		printf("%s<= Prev Addr\t:\t]%-14p[\t=>%s\n", color, tmp->prev,C_RESET);
		printf("%s<= Current Addr\t:\t]%-14p[\t=>%s\n", color, tmp,C_RESET);
		printf("%s<= Next Addr\t:\t]%-14p[\t=>%s\n", color, tmp->next,C_RESET);
		printf("%s<================================================>%s\n", color,C_RESET);
		printf("\n");
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokennew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel < abossel@student.42bangkok.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:29 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/25 10:38:46 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

t_token	*ft_tokennew(char *content, int type)
{
	t_token	*new_node;

	if (content == NULL)
		return (NULL);
	new_node = (t_token *)malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->token = content;
	new_node->type = type;
	new_node->piority = 0;
	new_node->quote = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

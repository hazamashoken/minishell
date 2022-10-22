/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokennew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:30:29 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/22 11:45:55 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../../cadet/minishell/includes/minishell.h"

t_token	*ft_tokennew(char *content, int type)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->token = content;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

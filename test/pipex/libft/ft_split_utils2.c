/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 08:00:41 by abossel           #+#    #+#             */
/*   Updated: 2022/12/07 08:45:52 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

/*
 * creates a new split with the string s
 */
char	**ft_split_new(char *s)
{
	char	**words;

	words = malloc(sizeof(char *) * 2);
	if (words == NULL)
		return (NULL);
	words[0] = s;
	words[1] = NULL;
	return (words);
}

/*
 * add the string s to the back of words
 * on success the functions will free words and return the new array
 * on failure the function will not free words and will return NULL
 * if words is NULL the function will attempt to create a new split
 * the string s will not be duplicated and will be added directly
 */
char	**ft_split_add_back(char **words, char *s)
{
	char	**words2;
	int		size;
	int		i;

	if (s == NULL)
		return (NULL);
	if (words == NULL)
		return (ft_split_new(s));
	size = ft_split_size(words);
	words2 = malloc(sizeof(char *) * (size + 2));
	if (words2 == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		words2[i] = words[i];
		i++;
	}
	words2[i] = s;
	words2[i + 1] = NULL;
	free(words);
	return (words2);
}

/*
 * add the string s to the front of words
 * on success the functions will free words and return the new array
 * on failure the function will not free words and will return NULL
 * if words is NULL the function will attempt to create a new split
 * the string s will not be duplicated and will be added directly
 */
char	**ft_split_add_front(char **words, char *s)
{
	char	**words2;
	int		size;
	int		i;

	if (s == NULL)
		return (NULL);
	if (words == NULL)
		return (ft_split_new(s));
	size = ft_split_size(words);
	words2 = malloc(sizeof(char *) * (size + 2));
	if (words2 == NULL)
		return (NULL);
	words2[0] = s;
	i = 0;
	while (i < size)
	{
		words2[i + 1] = words[i];
		i++;
	}
	words2[i + 1] = NULL;
	free(words);
	return (words2);
}

void	ft_split_print(char **words)
{
	int	size;
	int	i;

	if (words == NULL)
		return ;
	size = ft_split_size(words);
	i = 0;
	ft_printf("[");
	while (i < size)
	{
		if (i == 0)
			ft_printf(" %s", words[i]);
		else
			ft_printf(", %s", words[i]);
		i++;
	}
	ft_printf(" ]\n");
}

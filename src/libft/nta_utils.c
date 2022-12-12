/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nta_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 08:00:41 by abossel           #+#    #+#             */
/*   Updated: 2022/12/08 17:02:53 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
 * returns the size of array
 */
int	nta_size(void **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

/*
 * frees the array
 */
void	nta_free(void **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
 * creates a new null terminated array with the pointer p
 */
void	**nta_new(void *p)
{
	void	**array;

	array = malloc(sizeof(void *) * 2);
	if (array == NULL)
		return (NULL);
	array[0] = p;
	array[1] = NULL;
	return (array);
}

/*
 * add the pointer p to the back of array
 * on success the functions will free array and return the new array
 * on failure the function will not free array and will return NULL
 * if array is NULL the function will attempt to create a new array
 */
void	**nta_add_back(void **array, void *p)
{
	void	**array2;
	int		size;
	int		i;

	if (p == NULL)
		return (NULL);
	if (array == NULL)
		return (nta_new(p));
	size = nta_size(array);
	array2 = malloc(sizeof(void *) * (size + 2));
	if (array2 == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		array2[i] = array[i];
		i++;
	}
	array2[i] = p;
	array2[i + 1] = NULL;
	free(array);
	return (array2);
}

/*
 * add the pointer p to the front of array
 * on success the functions will free array and return the new array
 * on failure the function will not free array and will return NULL
 * if array is NULL the function will attempt to create a new array
 */
void	**nta_add_front(void **array, void *p)
{
	void	**array2;
	int		size;
	int		i;

	if (array == NULL)
		return (nta_new(p));
	size = nta_size(array);
	array2 = malloc(sizeof(void *) * (size + 2));
	if (array2 == NULL)
		return (NULL);
	array2[0] = p;
	i = 0;
	while (i < size)
	{
		array2[i + 1] = array[i];
		i++;
	}
	array2[i + 1] = NULL;
	free(array);
	return (array2);
}

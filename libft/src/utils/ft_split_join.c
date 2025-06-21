/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:33:51 by vlow              #+#    #+#             */
/*   Updated: 2025/06/01 16:55:03 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	join_s1(char **temp, char **s1, int *idx);
static int	join_s2(char **temp, char **s2, int i);

char	**ft_split_join(char **s1, char **s2)
{
	char	**temp;
	int		size;
	int		i;

	i = 0;
	size = ft_split_size(s1) + ft_split_size(s2);
	temp = malloc((size + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	if (!join_s1(temp, s1, &i))
		return (NULL);
	if (!join_s2(temp, s2, i))
		return (NULL);
	return (temp);
}

char	**split_free_join(char **arr1, char **arr2, int flag)
{
	char	**temp;

	if (!arr1)
	{
		arr1 = malloc(sizeof(char *));
		if (!arr1)
		{
			if (flag)
				split_free((void **)arr2);
			return (NULL);
		}
		ft_memset(arr1, 0, sizeof(char *));
	}
	if (!arr2)
		return (split_free((void **)arr1), NULL);
	temp = ft_split_join(arr1, arr2);
	split_free((void **)arr1);
	if (flag)
		split_free((void **)arr2);
	return (temp);
}

static int	join_s1(char **temp, char **s1, int *idx)
{
	int	i;
	int	size1;

	size1 = ft_split_size(s1);
	i = *idx;
	while (i < size1)
	{
		temp[i] = ft_strdup(s1[i]);
		if (!temp[i])
		{
			split_free((void **)temp);
			return (0);
		}
		i++;
	}
	*idx = i;
	return (1);
}

static int	join_s2(char **temp, char **s2, int i)
{
	int	j;
	int	size2;

	size2 = ft_split_size(s2);
	j = 0;
	while (j < size2)
	{
		temp[i] = ft_strdup(s2[j]);
		if (!temp[i])
		{
			split_free((void **)temp);
			return (0);
		}
		i++;
		j++;
	}
	temp[i] = NULL;
	return (1);
}

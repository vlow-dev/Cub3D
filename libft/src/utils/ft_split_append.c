/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:50:42 by vlow              #+#    #+#             */
/*   Updated: 2025/06/01 16:55:59 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	join_s1(char **temp, char **s1, int *idx);
static int	append_str(char **temp, char *str, int i);

char	**ft_split_append(char **s1, char *str)
{
	char	**temp;
	int		i;

	if (!s1 || !str)
		return (NULL);
	i = 0;
	temp = malloc((ft_split_size(s1) + 2) * sizeof(char *));
	if (!temp)
		return (NULL);
	if (!join_s1(temp, s1, &i))
		return (NULL);
	if (!append_str(temp, str, i))
		return (NULL);
	return (temp);
}

char	**split_free_append(char **arr, char *str, int flag)
{
	char	**temp;

	if (!arr)
	{
		arr = malloc(sizeof(char *));
		if (!arr)
		{
			if (flag)
				free(str);
			return (NULL);
		}
		ft_memset(arr, 0, sizeof(char *));
	}
	if (!str)
		return (split_free((void **)arr), NULL);
	temp = ft_split_append(arr, str);
	split_free((void **)arr);
	if (flag)
		free(str);
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

static int	append_str(char **temp, char *str, int i)
{
	temp[i] = ft_strdup(str);
	if (!temp[i])
	{
		split_free((void **)temp);
		return (0);
	}
	temp[++i] = NULL;
	return (1);
}
//
// int main(void)
// {
// 	// char *str = "Hello World Jajaja";
// 	char **s1 = malloc(sizeof(char *));
// 	char *s2 = "Lets append this";
//
// 	ft_memset(s1, 0, sizeof(char *));
// 	char **temp = ft_split_append(s1, s2);
// 	free(s1);
// 	s1 = temp;
//
// 	split_print(s1);
//
// 	return EXIT_SUCCESS;
// }

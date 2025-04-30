/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:16:13 by vlow              #+#    #+#             */
/*   Updated: 2025/04/16 23:16:15 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim_free(char *str, char *set)
{
	char	*temp;

	if (!str || !*str)
		return (str);
	temp = ft_strtrim(str, set);
	if (!temp)
		return (NULL);
	free(str);
	return (temp);
}

char	*ft_strjoin_free(char *s1, char *s2, int flag)
{
	char	*temp;

	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
		{
			if (flag)
				free(s2);
			return (free(s1), NULL);
		}
	}
	temp = ft_strjoin(s1, s2);
	if (!temp)
	{
		if (flag)
			free(s2);
		return (free(s1), NULL);
	}
	free(s1);
	if (flag)
		free(s2);
	return (temp);
}

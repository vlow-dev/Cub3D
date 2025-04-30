/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:22:37 by vlow              #+#    #+#             */
/*   Updated: 2025/03/17 13:29:09 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		if (little[j] == big[i])
		{
			while (little[j] && big[i + j])
			{
				if (big[i + j] != little[j])
					break ;
				j++;
			}
			if (!little[j])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}

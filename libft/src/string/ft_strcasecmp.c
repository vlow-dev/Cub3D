/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:36:40 by vlow              #+#    #+#             */
/*   Updated: 2025/04/16 23:15:27 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	char	a;
	char	b;

	while (*s1 || *s2)
	{
		a = ft_tolower(*s1);
		b = ft_tolower(*s2);
		if (a != b)
			break ;
		s1++;
		s2++;
	}
	return ((unsigned char)a - (unsigned char)b);
}

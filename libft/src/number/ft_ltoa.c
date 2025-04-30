/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:08:53 by vlow              #+#    #+#             */
/*   Updated: 2025/03/13 16:18:17 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_ltoa_ex(long int n);

char	*ft_ltoa(long int n)
{
	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	return (ft_ltoa_ex(n));
}

static char	*ft_ltoa_ex(long int n)
{
	int		neg;
	int		size;
	char	*buffer;

	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	size = ft_countdigits(n) + neg;
	buffer = malloc(sizeof(char) * (size + 1));
	if (!buffer)
		return (NULL);
	if (neg)
		buffer[0] = '-';
	buffer[size] = '\0';
	while (size != neg)
	{
		buffer[size - 1] = (n % 10) + '0';
		size--;
		n /= 10;
	}
	return (buffer);
}

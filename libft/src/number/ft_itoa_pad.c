/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_pad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:37:53 by vlow              #+#    #+#             */
/*   Updated: 2025/06/04 17:40:28 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_itoa_ex(int n, int pad);

/// @brief Convert integer to string representation
/// 
/// This function converts the given integer `n` to a string representation.
/// Special cases such as INT_MAX and INT_MIN are handled separately.
/// 
/// @param n The integer to be converted
/// @return A pointer to a null-terminated string representing the integer
char	*ft_itoa_pad(int n, int pad)
{
	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0 && pad <= 1)
		return (ft_strdup("0"));
	return (ft_itoa_ex(n, pad));
}

static void	ft_itoa_pad_ex2(int *n, int *neg, int *size)
{
	if (*n < 0)
	{
		*n = -(*n);
		*neg = 1;
	}
	*size = ft_countdigits(*n) + *neg;
}

static void	ft_itoa_pad_ex3(int pad, int size, int *pad_count)
{
	if (pad > size)
		*pad_count = pad - size;
	else
		*pad_count = 0;
}

static char	*ft_itoa_ex(int n, int pad)
{
	int		neg;
	int		size;
	int		pad_count;
	char	*buffer;

	neg = 0;
	ft_itoa_pad_ex2(&n, &neg, &size);
	ft_itoa_pad_ex3(pad, size, &pad_count);
	buffer = malloc(sizeof(char) * (size + pad_count + 1));
	if (!buffer)
		return (NULL);
	if (neg)
		buffer[0] = '-';
	buffer[size + pad_count] = '\0';
	while (size != neg)
	{
		buffer[(size + pad_count) - 1] = (n % 10) + '0';
		size--;
		n /= 10;
	}
	while (pad_count--)
		buffer[neg + pad_count] = '0';
	return (buffer);
}

/*#include <stdio.h>*/
/**/
/*int main(void)*/
/*{*/
/*	int test_values[] = {0, -2147483648, 2147483647, -12345, 12345};*/
/*	char *result;*/
/**/
/*	for (int i = 0; i < 5; i++)*/
/*	{*/
/*	result = ft_itoa(test_values[i]);*/
/*	if (result)*/
/*	{*/
/*		printf("ft_itoa(%d) = %s\n", test_values[i], result);*/
/*		free(result);*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("ft_itoa(%d) = NULL (Memory failed)\n", test_values[i]);*/
/*	}*/
/*	}*/
/**/
/*	return 0;*/
/*}*/

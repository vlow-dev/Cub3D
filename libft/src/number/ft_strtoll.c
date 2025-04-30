/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:31:43 by vlow              #+#    #+#             */
/*   Updated: 2025/03/25 20:20:19 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_nb(char c, int base);

long long	ft_strtoll(const char *str, char **endptr, int base)
{
	long long	amt;
	int			sign;

	amt = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (ft_issign(*str))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (convert_nb(*str, base) == -1)
			break ;
		amt = amt * base + convert_nb(*str, base);
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (amt * sign);
}

static int	convert_nb(char c, int base)
{
	int	nb;

	nb = 0;
	if (ft_isdigit(c))
		nb = c - '0';
	else if (ft_isupper(c))
		nb = c - 'A' + 10;
	else if (ft_islower(c))
		nb = c - 'a' + 10;
	else
		return (-1);
	if (nb >= base)
		return (-1);
	return (nb);
}

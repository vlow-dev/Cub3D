/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:32:59 by vlow              #+#    #+#             */
/*   Updated: 2025/06/01 16:52:07 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	split_free(void **str)
{
	void	**temp;

	if (!str)
		return (0);
	temp = str;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(str);
	return (1);
}

int	ft_split_size(char **arr)
{
	int	count;

	count = 0;
	while (*arr)
	{
		count++;
		arr++;
	}
	return (count);
}

void	split_print(char **str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_printf("Split returned NULL.\n");
		return ;
	}
	ft_printf("Split result:\n");
	while (str[i])
	{
		ft_printf("[%d]: [%s]\n", i, str[i]);
		i++;
	}
	ft_printf("[%d]: [%s]\n", i, str[i]);
}

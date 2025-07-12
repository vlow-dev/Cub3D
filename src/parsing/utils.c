/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:37 by ialee             #+#    #+#             */
/*   Updated: 2025/07/12 21:38:44 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../include/parsing.h"
#include <stdlib.h>
#include <fcntl.h>

char	*unwhite(char *line)
{
	char	*itr[3];
	int		count;

	itr[0] = line;
	count = 0;
	while (*(itr[0]))
	{
		if (ft_isspace(*(itr[0])))
			count++;
		(itr[0])++;
	}
	itr[1] = malloc(sizeof(char) * (ft_strlen(line) - count + 1));
	itr[0] = line;
	itr[2] = itr[1];
	while (*(itr[0]))
	{
		if (ft_isspace(*(itr[0])))
		{
			(itr[0])++;
			continue ;
		}
		*(itr[2])++ = *(itr[0])++;
	}
	*(itr[2]) = '\0';
	return (itr[1]);
}

char	*get_path_direction(char *line)
{
	char	*clean;
	char	*ret;

	clean = unwhite(line);
	ret = ft_strdup(&clean[2]);
	free(clean);
	return (ret);
}

static int	assign_rgb(char **rgb, int **j)
{
	(*j)[0] = ft_atoi(rgb[0]);
	(*j)[1] = ft_atoi(rgb[1]);
	(*j)[2] = ft_atoi(rgb[2]);
	if ((*j)[0] < 0 || (*j)[0] > 255 ||
		(*j)[1] < 0 || (*j)[1] > 255 ||
		(*j)[2] < 0 || (*j)[2] > 255)
	{
		free(*j);
		return (1);
	}
	return (0);
}

int	get_colours(char *line)
{
	char	*clean;
	char	**rgb;
	int		i;
	char	**rgb_itr;
	int		*j;

	clean = unwhite(line);
	rgb = ft_split(&clean[1], ',');
	rgb_itr = rgb;
	j = malloc(sizeof(int) * 4);
	i = 1;
	while (*(++rgb_itr))
		i++;
	if (i != 3)
		return (free(j), free(clean), split_free((void **)rgb), -1);
	if (assign_rgb(rgb, &j))
		return (free(j), free(clean), split_free((void **)rgb), -1);
	i = (0xFF << 24) | (j[0] << 16) | (j[1] << 8) | j[2];
	split_free((void **)rgb);
	free(j);
	free(clean);
	return (i);
}

int	safe_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

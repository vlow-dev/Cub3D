/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:34 by ialee             #+#    #+#             */
/*   Updated: 2025/07/12 21:19:35 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"
#include "libft.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->tex[i] && i < TEX_SIZE)
		free(map->tex[i++]);
	i = 0;
	split_free((void **)map->maps);
	split_free((void **)map->door_open);
	free(map);
}

void	free_str(void *s)
{
	free(s);
}

int	info_assign(t_map *map, char **raw_file, int line_idx)
{
	if (ft_strncmp("NO", raw_file[line_idx], 2) == 0)
		(map)->tex[TEX_NO] = get_path_direction(raw_file[line_idx]);
	else if (ft_strncmp("SO", raw_file[line_idx], 2) == 0)
		(map)->tex[TEX_SO] = get_path_direction(raw_file[line_idx]);
	else if (ft_strncmp("WE", raw_file[line_idx], 2) == 0)
		(map)->tex[TEX_WE] = get_path_direction(raw_file[line_idx]);
	else if (ft_strncmp("EA", raw_file[line_idx], 2) == 0)
		(map)->tex[TEX_EA] = get_path_direction(raw_file[line_idx]);
	else if (ft_strncmp("DO", raw_file[line_idx], 2) == 0)
		(map)->tex[TEX_DO] = get_path_direction(raw_file[line_idx]);
	else
		return (0);
	return (1);
}

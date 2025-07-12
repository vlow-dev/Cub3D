/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:34 by ialee             #+#    #+#             */
/*   Updated: 2025/06/27 15:28:29 by ialee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < TEX_SIZE)
		free(map->tex[i++]);
	i = 0;
	while (i < map->y_size)
		free(map->maps[i++]);
	free(map->maps);
	free(map->pp);
	split_free(map->door_open);
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

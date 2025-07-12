/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:34 by ialee             #+#    #+#             */
/*   Updated: 2025/06/27 15:28:29 by ialee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/parsing.h"

t_validify	*init_valid(t_map *map)
{
	int			y;
	int			x;
	t_validify	*v;

	v = malloc(sizeof(t_validify));
	v->map = map;
	v->visited = malloc(sizeof(int *) * map->y_size);
	y = 0;
	while (y < map->y_size)
	{
		v->visited[y] = malloc(sizeof(int) * safe_strlen(map->maps[y]));
		x = 0;
		while (x < safe_strlen(map->maps[y]))
			v->visited[y][x++] = 0;
		y++;
	}
	return (v);
}

void	free_valid(t_map *map, t_validify *v)
{
	int	y;

	y = 0;
	while (y < map->y_size)
	{
		free(v->visited[y++]);
	}
	free(v->visited);
	free(v);
}

void	flood_fill(t_validify *v, int x, int y, int *is_err)
{
	char	value;

	if (*is_err == 1)
		return ;
	if (x < 0 || x >= safe_strlen(v->map->maps[y])
		|| y < 0 || y >= v->map->y_size)
	{
		*is_err = 1;
		return ;
	}
	value = v->map->maps[y][x];
	if (value == '1' || v->visited[y][x] == 1)
		return ;
	if (value == 'O' || value == 'D' || value == '0' || value == 'N'
		|| value == 'S' || value == 'E' || value == 'W')
		v->visited[y][x] = 1;
	else
	{
		*is_err = 1;
		return ;
	}
	flood_fill(v, x - 1, y, is_err);
	flood_fill(v, x + 1, y, is_err);
	flood_fill(v, x, y - 1, is_err);
	flood_fill(v, x, y + 1, is_err);
}

int	is_map_valid(t_map *map)
{
	int			x;
	int			y;
	static int	is_err;
	t_validify	*v;

	v = init_valid(map);
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < safe_strlen(map->maps[y]))
		{
			if (map->maps[y][x] == 'N' || map->maps[y][x] == 'S'
				|| map->maps[y][x] == 'W'
				|| map->maps[y][x] == 'E')
			{
				flood_fill(v, x, y, &is_err);
				break ;
			}
			x++;
		}
		y++;
	}
	free_valid(map, v);
	return (is_err == 0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/parsing.h"

t_validify	*init_valid(t_map *map)
{
	int			y;
	t_validify	*v;

	v = malloc(sizeof(t_validify));
	v->map = map;
	v->visited = malloc(sizeof(int *) * map->y_size);
	y = 0;
	while (y < map->y_size)
	{
		v->visited[y] = malloc(sizeof(int) * safe_strlen(map->maps[y]));
		y++;
	}
	return (v);
}

void	flood_fill(t_validify *v, int x, int y, int *is_err)
{
	int	value;

	if (*is_err == 1)
		return ;
	if (x < 0 || x >= v->map->x_size || y < 0 || y >= v->map->y_size)
	{
		*is_err = 1;
		return ;
	}
	value = v->map->maps[y][x];
	if (value == 1 || v->visited[y][x] == 1)
		return ;
	if (value == 'O' || value == 'D' || value == 0 || value == 'N'
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
	int			is_err;
	t_validify	*v;

	v = init_valid(map);
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
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
	return (is_err == 0);
}

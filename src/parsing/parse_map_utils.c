#include "cub3d.h"
#include "parsing.h"

void	flood_fill(t_map *map, int x, int y, int *is_err)
{
	int	value;

	if (*is_err == 1)
		return ;
	if (x < 0 || x >= map->x_max || y < 0 || y >= map->y_max)
	{
		*is_err = 1;
		return ;
	}
	value = map->point[y][x].value;
	if (value == 1 || map->point[y][x].visited == true)
		return ;
	if (value == 'O' || value == 'D' || value == 0 || value == 'N'
		|| value == 'S' || value == 'E' || value == 'W')
		map->point[y][x].visited = true;
	else
	{
		*is_err = 1;
		return ;
	}
	flood_fill(map, x - 1, y, is_err);
	flood_fill(map, x + 1, y, is_err);
	flood_fill(map, x, y - 1, is_err);
	flood_fill(map, x, y + 1, is_err);
}

bool	is_valid_map(t_unvalidated_map *map)
{
	int	x;
	int	y;
	int	is_err;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			if (map->point[y][x].value == 'N' || map->point[y][x].value == 'S'
				|| map->point[y][x].value == 'W'
				|| map->point[y][x].value == 'E')
			{
				flood_fill(map, x, y, &is_err);
				break ;
			}
			x++;
		}
		y++;
	}
	if (is_err == 0)
		return (true);
	ft_putstr_fd("Error\nInvalid map\n", 2);
	return (false);
}

bool	is_valid_player(t_unvalidated_map *map)
{
	int	player_count;
	int	x;
	int	y;

	y = 0;
	player_count = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			if (map->point[y][x].value == 'N'
				|| map->point[y][x].value == 'S'
				|| map->point[y][x].value == 'W'
				|| map->point[y][x].value == 'E')
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count == 1)
		return (true);
	ft_putstr_fd("Error\nInvalid player count\n", 2);
	return (false);
}

bool	is_map(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 0 && str[i] != '1' && str[i] != '0'
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != 'D' && str[i] != 'O'
			&& str[i] != '\n')
			return (false);
		if (ft_isspace(str[i]) == 1)
			count++;
		i++;
	}
	if (count == ft_strlen(str))
		return (false);
	return (true);
}

void	init_map_points(t_unvalidated_map *map)
{
	int	y;

	map->point = malloc(map->y_max * sizeof(t_point *));
	if (map->point == NULL)
	{
		ft_putstr_fd("Error malloc\n", 2);
		free_umap(map);
		exit(1);
	}
	y = 0;
	while (y < map->y_max)
	{
		map->point[y] = malloc(map->x_max * sizeof(t_point));
		if (map->point[y] == NULL)
		{
			ft_putstr_fd("Error malloc\n", 2);
			free_umap(map);
			exit(1);
		}
		y++;
	}
}

#include "cub3d.h"
#include "cub3d.h"

void	get_map_size(t_unvalidated_map *map, int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if (is_map(str) == true)
		{
			if ((int)ft_strlen(str) > map->x_size)
				map->x_size = ft_strlen(str) - 1;
			map->y_size++;
		}
		free(str);
		str = get_next_line(fd);
	}
}

void	parse_map_size(t_unvalidated_map *map, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error opening file\n", 2);
		free_umap(map);
		exit(1);
	}
	get_map_size(map, fd);
	close(fd);
	if (map->x_size == 0 || map->y_size == 0)
	{
		ft_putstr_fd("Error\nInvalid map size\n", 2);
		delete_and_free_vars(vars);
		exit(1);
	}
}

void	get_map_values_row(t_unvalidated_map *map, char *str, int y)
{
	int	x;

	x = 0;
	while (x < map->x_size)
	{
		if (x >= (int)ft_strlen(str) || ft_isspace(str[x]) == 1)
			map->point[y][x].value = -1;
		else if (ft_isdigit(str[x]) == 1)
			map->point[y][x].value = str[x] - '0';
		else
			map->point[y][x].value = str[x];
		map->point[y][x].x = x;
		map->point[y][x].y = y;
		map->point[y][x].visited = false;
		x++;
	}
}

void	get_map_values(t_unvalidated_map *map, int fd)
{
	char	*str;
	int		y;

	y = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (is_map(str) == true)
		{
			get_map_values_row(m, str, y);
			y++;
		}
		free(str);
		str = get_next_line(fd);
	}
}

void	parse_map_values(t_unvalidated_map *m, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error opening file\n", 2);
		free_umap(m);
		exit(1);
	}
	get_map_values(m, fd);
	close (fd);
}

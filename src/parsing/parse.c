#include "cub3d.h"
#include "parsing.h"

void	free_umap(t_unvalidated_map *map)
{
	int	y;

	if (vars->map.point != NULL)
	{
		y = 0;
		while (y < vars->map.y_size && vars->map.point[y] != NULL)
		{
			if (vars->map.point[y] != NULL)
				free(vars->map.point[y]);
			y++;
		}
		free(vars->map.point);
	}
}

// parse_texture & parse_color will exit automatically on any error
t_result	*parse_file(char **argv)
{
	t_map		*map;

	map = malloc(sizeof(t_map));
	// init_map;
	if (is_valid_file(argv[1]) == false)
		exit(1);
	parse_texture(map, argv[1]);
	parse_color(map, argv[1]);
	if (!is_texture_filled(vars->texture))
	{
		free_map(map);
		exit(1);
	}
	parse_map(map, argv[1]);
	return result_ok(map);
}

void	parse_map(t_map *map, char *file)
{
	t_unvalidated_map	*m;

	m = malloc(sizeof(t_unvalidated_map));
	parse_map_size(m, file);
	init_map_points(m);
	parse_map_values(m, file);
	if (!is_valid_player(m) || !is_valid_map(m))
	{
		free_umap(m);
		free_map(map);
		exit(-1);
	}
	extract_validated(map, m)
	free_umap(m);
}

// get_color_data will exit on err.
void	parse_color(t_map *map, char *file)
{
	int		fd;
	char	*is_error;

	is_error = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error opening file\n", 2);
		free_map(map);
		exit(1);
	}
	get_color_data(map, fd, is_error);
	close(fd);
}

// get_texture_data will exit on err.
void	parse_texture(t_map *map, char *file)
{
	int			fd;
	char		*is_error;

	is_error = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error opening file\n", 2);
		free_map(map);
		exit(1);
	}
	get_texture_data(map, fd, &is_error);
	close(fd);
}

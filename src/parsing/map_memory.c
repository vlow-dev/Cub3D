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
	free(map);
}

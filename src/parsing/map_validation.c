#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/parsing.h"

// Enhanced version using flood fill algorithm
static int flood_fill_check(char **map, int **visited, int x, int y, int height)
{
	int	width;

	width = safe_strlen(map[x]);
    if (x < 0 || y < 0 || x >= height)
        return (0);
    if (y >= width)
        return (0);
    if (visited[x][y] || map[x][y] == '1')
        return (1);
    if (map[x][y] == ' ')
        return (0);
    if (!is_valid_floor(map[x][y]))
        return (0);
    visited[x][y] = 1;
	if (!flood_fill_check(map, visited, x - 1, y, height)
        || !flood_fill_check(map, visited, x + 1, y, height)
        || !flood_fill_check(map, visited, x, y - 1, height)
        || !flood_fill_check(map, visited, x, y + 1, height))
        return (0);
    return (1);
}

static int free_visited(int **visited, int height, int ret)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
    free(visited);
	return (ret);
}

static int	seek_player(char **map, int height)
{
	int	i;
	int	j;
	int	width;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (i < height)
    {
        width = safe_strlen(map[i]);
		while (j < width)
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || 
                map[i][j] == 'E' || map[i][j] == 'W')
                player_count++;
			j++;
        }
		i++;
    }
	return (player_count);
}

static int	flood_fill_logic(char **map, int height, int **visited)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	j = 0;
	while (i < height)
    {
        width = safe_strlen(map[i]);
		while (j < width)
        {
            if (is_valid_floor(map[i][j]) && !visited[i][j])
            {
                if (!flood_fill_check(map, visited, i, j, height))
                {
					return (free_visited(visited, height, 0));
                }
            }
			j++;
        }
		i++;
    }
	return (1);
}

int is_map_valid(char **map)
{
	int	i;
    int height;
	int	max_width;
    int **visited;
   
	i = 0;
    if (!map || !map[0])
	{
        return (0);
	}
	max_width = get_max_width(map, &height);
    visited = malloc(sizeof(int *) * height);
    if (!visited)
		return (0);
	while (i < height)
    {
        visited[i] = calloc(max_width, sizeof(int));
        if (!visited[i++])
			return (free_visited(visited, height, 0));
    }
    if (seek_player(map, height) != 1)
		return (free_visited(visited, height, 0));
	if (!flood_fill_logic(map, height, visited))
		return (0);
	return (free_visited(visited, height, 1)); 
}

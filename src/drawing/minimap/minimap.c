#include "../../../libft/include/libft.h"
#include "../../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static void	actual_draw(t_data *data, int **matrix, unsigned int *color)
{
	(*matrix)[7] = (*matrix)[4] - (MMAP_RADIUS + MMAP_MARGIN);
	(*matrix)[8] = (*matrix)[5] - (MMAP_RADIUS + MMAP_MARGIN);
	if ((*matrix)[7] * (*matrix)[7] + (*matrix)[8]
			* (*matrix)[8] <= MMAP_RADIUS * MMAP_RADIUS)
		my_pixel_put(data, (*matrix)[4], (*matrix)[5], *color);
}

static int	assign_color(t_data *data, int **matrix, unsigned int *color)
{
	if (data->map.maps[(*matrix)[1]][(*matrix)[0]] == '1')
		*color = MM_WALL;
	else if (data->map.maps[(*matrix)[1]][(*matrix)[0]] == '0'
			|| data->map.maps[(*matrix)[1]][(*matrix)[0]] == 'N'
			|| data->map.maps[(*matrix)[1]][(*matrix)[0]] == 'S'
			||data->map.maps[(*matrix)[1]][(*matrix)[0]] == 'W'
			|| data->map.maps[(*matrix)[1]][(*matrix)[0]] == 'E')
		*color = MM_FLOOR;
	else if (data->map.maps[(*matrix)[1]][(*matrix)[0]] == '2'
			&& !data->map.door_open[(*matrix)[1]][(*matrix)[0]])
		*color = MM_DOOR_C;
	else if (data->map.maps[(*matrix)[1]][(*matrix)[0]] == '2'
			&& data->map.door_open[(*matrix)[1]][(*matrix)[0]])
		*color = MM_DOOR_O;
	else
		return (1);
	return (0);
}

static void	draw_logic(t_data *data, int **matrix, unsigned int *color)
{
	if (assign_color(data, &(*matrix), color))
		return ;
	(*matrix)[3] = -1;
	while (++(*matrix)[3] < data->mini.z_scale)
	{
		(*matrix)[2] = -1;
		while (++(*matrix)[2] < data->mini.z_scale)
		{
			(*matrix)[4] = (int)((double)((*matrix)[0]
						* data->mini.z_scale + (*matrix)[2]
						+ data->mini.p_ox) + 0.5);
			(*matrix)[5] = (int)((double)((*matrix)[1]
						* data->mini.z_scale + (*matrix)[3]
						+ data->mini.p_oy) + 0.5);
			if ((*matrix)[4] < 0 || (*matrix)[5] < 0
						|| (*matrix)[4] >= WIDTH
						|| (*matrix)[5] >= HEIGHT)
				continue ;
			actual_draw(data, matrix, color);
		}
	}
}

// int	x; 0
// int	y; 1
// int	dx; 2
// int	dy; 3
// int tx; 4
// int ty; 5
// int len; 6
// int ddx; 7
// int ddy; 8
void	draw_minimap(t_data *data)
{
	int				*matrix;
	unsigned int	color;

	matrix = malloc(sizeof(int)* 9);
	color = WHITE;
	minimap_center_player(data);
	matrix[1] = -1;
	while (++(matrix[1]) < data->map.y_size)
	{
		matrix[0] = -1;
		matrix[6] = ft_strlen(data->map.maps[matrix[1]]);
		while (++(matrix[0]) < matrix[6])
			draw_logic(data, (int **)&matrix, &color);
	}
	draw_minimap_circle_border(data);
	draw_minimap_player(data);
}

void	init_minimap(t_data *data)
{
	data->mini.scale_x = (WIDTH * MMAP_SIZE) / (double)data->map.x_size;
	data->mini.scale_y = (HEIGHT * MMAP_SIZE) / (double)data->map.y_size;
	data->mini.scale = fmin(data->mini.scale_x, data->mini.scale_y);
	data->mini.zoom_factor = 1.0;
	data->mini.z_scale = (int)(data->mini.scale * data->mini.zoom_factor) + 0.5;
}

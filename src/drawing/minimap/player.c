#include "../../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>

void	minimap_center_player(t_data *data)
{
	int	cx;
	int	cy;

	cx = MMAP_RADIUS + MMAP_MARGIN;
	cy = MMAP_RADIUS + MMAP_MARGIN;
	data->mini.p_x = data->player.pos_x * data->mini.z_scale;
	data->mini.p_y = data->player.pos_y * data->mini.z_scale;
	data->mini.p_ox = cx - data->mini.p_x;
	data->mini.p_oy = cy - data->mini.p_y;
}

	// 0int cx = MMAP_RADIUS + MMAP_MARGIN;
	// 1int cy = MMAP_RADIUS + MMAP_MARGIN;
	// 2int y = -1;
	// 3int x;
	// 4int	size = 5;
	// 5int px;
	// 6int py;
void	draw_minimap_player(t_data *data)
{
	int	matrix[7];

	matrix[0] = MMAP_RADIUS + MMAP_MARGIN;
	matrix[1] = MMAP_RADIUS + MMAP_MARGIN;
	matrix[2] = -1;
	matrix[3] = 0;
	matrix[4] = 5;
	matrix[5] = 0;
	matrix[6] = 0;
	while (++matrix[2] < matrix[4])
	{
		matrix[3] = -1;
		while (++matrix[3] < matrix[4])
		{
			matrix[5] = matrix[0] + matrix[3];
			matrix[6] = matrix[1] + matrix[2];
			if (matrix[5] >= 0 && matrix[6] >= 0
				&& matrix[5] < WIDTH && matrix[6] < HEIGHT)
				my_pixel_put(data, matrix[5], matrix[6], RED);
		}
	}
}

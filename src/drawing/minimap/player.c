/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:03 by vlow              #+#    #+#             */
/*   Updated: 2025/07/07 16:07:11 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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

// 0int cx;
// 1int cy;
// 2int y = -1;
// 3int x;
// 4int	size = 5;
// 5int px;
// 6int py;
void	draw_minimap_player(t_data *data)
{
	int	matrix[7];

	matrix[2] = -1;
	matrix[3] = 0;
	matrix[4] = 5;
	matrix[5] = 0;
	matrix[6] = 0;
	matrix[0] = data->mini.p_x + data->mini.p_ox - (int)(matrix[4] / 2);
	matrix[1] = data->mini.p_y + data->mini.p_oy - (int)(matrix[4] / 2);
	while (++matrix[2] < matrix[4])
	{
		matrix[3] = -1;
		while (++matrix[3] < matrix[4])
		{
			matrix[5] = matrix[0] + matrix[3];
			matrix[6] = matrix[1] + matrix[2];
			if (matrix[5] >= 0 && matrix[6] >= 0
				&& matrix[5] < WIDTH && matrix[6] < HEIGHT)
				my_pixel_put(data, matrix[5], matrix[6], MM_PLAYER);
		}
	}
}

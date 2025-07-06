/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:23 by vlow              #+#    #+#             */
/*   Updated: 2025/07/06 17:14:38 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->img.addr + (y * data->img.line_len
				+ x * (data->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void	draw_image_trans(t_data *data, t_img *src, int dst_x, int dst_y)
{
	int				x;
	int				y;
	char			*src_pixel;
	unsigned int	color;

	y = 0;
	while (y < src->y)
	{
		x = 0;
		while (x < src->x)
		{
			src_pixel = src->addr + y * src->line_len + x * (src->bpp / 8);
			color = *(unsigned int *)src_pixel;
			if (color != 0xFF000000)
				my_pixel_put(data, dst_x + x, dst_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_compass(t_data *data)
{
	int		x;
	int		y;
	t_img	*frame;

	data->compass.timer += data->time.delta_time;
	if (data->compass.timer >= ANISPEED)
	{
		data->compass.idx = (data->compass.idx + 1) % COMPASS_FRAME;
		data->compass.timer = 0;
	}
	frame = &data->c_frame[data->compass.idx];
	x = WIDTH - frame->x - 10;
	y = HEIGHT - frame->y - 10;
	draw_image_trans(data, frame, x, y);
}

void	init_player(t_data *data)
{
	char	st_dir;

	data->player.pos_x = data->map.pp->x + 0.5;
	data->player.pos_y = data->map.pp->y + 0.5;
	st_dir = data->map.pp->dir;
	if (st_dir == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
	}
	else if (st_dir == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
	}
	else if (st_dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.66;
	}
	else if (st_dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.66;
	}
}

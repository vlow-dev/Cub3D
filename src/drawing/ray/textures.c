/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:15 by vlow              #+#    #+#             */
/*   Updated: 2025/07/06 17:13:18 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include <sys/time.h>

void	ray_tex_init(t_data *data)
{
	data->draw.height = (int)(HEIGHT / data->ray.perpDist);
	data->draw.start = -data->draw.height / 2 + HEIGHT / 2;
	if (data->draw.start < 0)
		data->draw.start = 0;
	data->draw.end = data->draw.height / 2 + HEIGHT / 2;
	if (data->draw.end >= HEIGHT)
		data->draw.end = HEIGHT - 1;
}

void	ray_tex_door(t_data *data, int side)
{
	double	wall_x;

	if (!side)
		wall_x = data->player.pos_y
			+ data->ray.perpDist * data->ray.y;
	else
		wall_x = data->player.pos_x
			+ data->ray.perpDist * data->ray.x;
	wall_x -= floor(wall_x);
	data->draw.tex_side = TEX_DO;
	data->draw.tex_x = (int)(wall_x
			* (double)data->tex[data->draw.tex_side].x);
}

void	ray_tex_sides(t_data *data, int side)
{
	data->draw.wall_x = data->player.pos_x
		+ data->ray.perpDist * data->ray.x;
	if (!side)
		data->draw.wall_x = data->player.pos_y
			+ data->ray.perpDist * data->ray.y;
	data->draw.wall_x -= floor(data->draw.wall_x);
	if (!side)
	{
		if (data->ray.x > 0)
			data->draw.tex_side = TEX_NO;
		else
			data->draw.tex_side = TEX_SO;
	}
	else
	{
		if (data->ray.y > 0)
			data->draw.tex_side = TEX_EA;
		else
			data->draw.tex_side = TEX_WE;
	}
	data->draw.tex_x = (int)(data->draw.wall_x
			* (double)data->tex[data->draw.tex_side].x);
	if ((!side && data->ray.x > 0) || (side && data->ray.y < 0))
		data->draw.tex_x = data->tex[data->draw.tex_side].x
			- data->draw.tex_x - 1;
}

static void	ray_tex_wall(t_data *data, int ray, int y)
{
	int		wall_step;
	int		tex_y;
	int		color;
	char	*pxl;

	wall_step = y * 2 - HEIGHT + data->draw.height;
	tex_y = (wall_step * data->tex[data->draw.tex_side].y)
		/ (2 * data->draw.height);
	pxl = data->tex[data->draw.tex_side].addr + tex_y
		* data->tex[data->draw.tex_side].line_len
		+ data->draw.tex_x * (data->tex[data->draw.tex_side].bpp / 8);
	color = *(int *)pxl;
	my_pixel_put(data, ray, y, color);
}

void	ray_tex_draw(t_data *data, int ray)
{
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < data->draw.start)
			my_pixel_put(data, ray, y, data->map.ceiling);
		else if (y <= data->draw.end)
			ray_tex_wall(data, ray, y);
		else
			my_pixel_put(data, ray, y, data->map.floor);
	}
}

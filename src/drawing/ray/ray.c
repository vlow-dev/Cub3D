/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:09 by vlow              #+#    #+#             */
/*   Updated: 2025/07/07 13:38:36 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"
#include <math.h>

static void	ray_init(t_data *data, int ray)
{
	data->ray.cam_x = 2.0 * ray / (double)WIDTH - 1.0;
	data->ray.x = data->player.dir_x + (data->player.plane_x * data->ray.cam_x);
	data->ray.y = data->player.dir_y + (data->player.plane_y * data->ray.cam_x);
	data->ray.dist_x = fabs(1.0 / data->ray.x);
	data->ray.dist_y = fabs(1.0 / data->ray.y);
	data->ray.tile_x = (int)data->player.pos_x;
	data->ray.tile_y = (int)data->player.pos_y;
}

static void	ray_stepdir(t_data *data)
{
	if (data->ray.x < 0)
	{
		data->ray.side_x = -1;
		data->ray.len_x = (data->player.pos_x
				- data->ray.tile_x) * data->ray.dist_x;
	}
	else
	{
		data->ray.side_x = 1;
		data->ray.len_x = ((data->ray.tile_x + 1.0)
				- data->player.pos_x) * data->ray.dist_x;
	}
	if (data->ray.y < 0)
	{
		data->ray.side_y = -1;
		data->ray.len_y = (data->player.pos_y
				- data->ray.tile_y) * data->ray.dist_y;
	}
	else
	{
		data->ray.side_y = 1;
		data->ray.len_y = ((data->ray.tile_y + 1.0)
				- data->player.pos_y) * data->ray.dist_y;
	}
}

static int	ray_door(t_data *data, int *side)
{
	char	c;

	c = data->map.maps[data->ray.tile_y][data->ray.tile_x];
	if (c == '1')
		data->ray.door = 0;
	else if (c == 'D'
		&& data->map.door_open[data->ray.tile_y][data->ray.tile_x] < 1.0)
	{
		data->ray.door = 1;
		if (!*side)
			data->ray.perp_dist = ((data->ray.tile_x
						+ 0.5 + data->ray.side_x * 0.5
						* data->map.door_open[data->ray.tile_y]
					[data->ray.tile_x])
					- data->player.pos_x) / data->ray.x;
		else
			data->ray.perp_dist = ((data->ray.tile_y + 0.5
						+ data->ray.side_y * 0.5
						* data->map.door_open[data->ray.tile_y]
					[data->ray.tile_x])
					- data->player.pos_y) / data->ray.y;
	}
	else
		return (0);
	return (1);
}

static void	ray_dda(t_data *data, int *side)
{
	while (1)
	{
		if (data->ray.len_x < data->ray.len_y)
		{
			data->ray.len_x += data->ray.dist_x;
			data->ray.tile_x += data->ray.side_x;
			*side = 0;
		}
		else
		{
			data->ray.len_y += data->ray.dist_y;
			data->ray.tile_y += data->ray.side_y;
			*side = 1;
		}
		if (ray_door(data, side))
			break ;
	}
	if (*side == 0)
		data->ray.perp_dist = (data->ray.tile_x - data->player.pos_x
				+ (1 - data->ray.side_x) / 2.0) / data->ray.x;
	else
		data->ray.perp_dist = (data->ray.tile_y - data->player.pos_y
				+ (1 - data->ray.side_y) / 2.0) / data->ray.y;
}

void	raycasting(t_data *data)
{
	int	ray;
	int	side;

	ray = -1;
	side = -1;
	while (++ray < WIDTH)
	{
		ray_init(data, ray);
		ray_stepdir(data);
		ray_dda(data, &side);
		ray_tex_init(data);
		if (data->ray.door)
			ray_tex_door(data, side);
		else
			ray_tex_sides(data, side);
		ray_tex_draw(data, ray);
	}
}

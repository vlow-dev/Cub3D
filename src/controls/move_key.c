/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:33 by vlow              #+#    #+#             */
/*   Updated: 2025/07/06 15:50:40 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	w_key(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVESPEED
		* data->time.delta_time;
	new_y = data->player.pos_y + data->player.dir_y * MOVESPEED
		* data->time.delta_time;
	if (valid_tile(data, data->player.pos_y, new_x))
		data->player.pos_x = new_x;
	if (valid_tile(data, new_y, data->player.pos_x))
		data->player.pos_y = new_y;
}

void	s_key(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVESPEED
		* data->time.delta_time;
	new_y = data->player.pos_y - data->player.dir_y * MOVESPEED
		* data->time.delta_time;
	if (valid_tile(data, data->player.pos_y, new_x))
		data->player.pos_x = new_x;
	if (valid_tile(data, new_y, data->player.pos_x))
		data->player.pos_y = new_y;
}

void	a_key(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.plane_x * MOVESPEED
		* data->time.delta_time;
	new_y = data->player.pos_y - data->player.plane_y * MOVESPEED
		* data->time.delta_time;
	if (valid_tile(data, data->player.pos_y, new_x))
		data->player.pos_x = new_x;
	if (valid_tile(data, new_y, data->player.pos_x))
		data->player.pos_y = new_y;
}

void	d_key(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.plane_x * MOVESPEED
		* data->time.delta_time;
	new_y = data->player.pos_y + data->player.plane_y * MOVESPEED
		* data->time.delta_time;
	if (valid_tile(data, data->player.pos_y, new_x))
		data->player.pos_x = new_x;
	if (valid_tile(data, new_y, data->player.pos_x))
		data->player.pos_y = new_y;
}

void	lr_key(t_data *data)
{
	double	temp_dir_x;
	double	temp_plane_x;
	double	angle;

	temp_dir_x = data->player.dir_x;
	temp_plane_x = data->player.plane_x;
	if (data->player.key_left)
	{
		angle = -ROTSPEED * data->time.delta_time;
	}
	else
		angle = ROTSPEED * data->time.delta_time;
	data->player.dir_x = data->player.dir_x * cos(angle)
		- data->player.dir_y * sin(angle);
	data->player.dir_y = temp_dir_x * sin(angle)
		+ data->player.dir_y * cos(angle);
	data->player.plane_x = data->player.plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = temp_plane_x * sin(angle)
		+ data->player.plane_y * cos(angle);
}

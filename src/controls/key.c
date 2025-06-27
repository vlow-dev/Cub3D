/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:33 by vlow              #+#    #+#             */
/*   Updated: 2025/06/27 12:26:34 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include <sys/time.h>

void	w_key(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVESPEED;
	new_y = data->player.pos_y + data->player.dir_y * MOVESPEED;
	if (valid_tile(data, data->map.maps[(int)data->player.pos_y][(int)new_x],
		(int)data->player.pos_y, (int)new_x))
		data->player.pos_x = new_x;
	if (valid_tile(data, data->map.maps[(int)new_y][(int)data->player.pos_x],
		(int)new_y, (int)data->player.pos_x))
		data->player.pos_y = new_y;
}

void	s_key(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVESPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVESPEED;
	if (valid_tile(data, data->map.maps[(int)data->player.pos_y][(int)new_x],
		(int)data->player.pos_y, (int)new_x))
		data->player.pos_x = new_x;
	if (valid_tile(data, data->map.maps[(int)new_y][(int)data->player.pos_x],
		(int)new_y, (int)data->player.pos_x))
		data->player.pos_y = new_y;
}

void	a_key(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.plane_x * MOVESPEED;
	new_y = data->player.pos_y - data->player.plane_y * MOVESPEED;
	if (valid_tile(data, data->map.maps[(int)data->player.pos_y][(int)new_x],
		(int)data->player.pos_y, (int)new_x))
		data->player.pos_x = new_x;
	if (valid_tile(data, data->map.maps[(int)new_y][(int)data->player.pos_x],
		(int)new_y, (int)data->player.pos_x))
		data->player.pos_y = new_y;
}

void	d_key(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.plane_x * MOVESPEED;
	new_y = data->player.pos_y + data->player.plane_y * MOVESPEED;
	if (valid_tile(data, data->map.maps[(int)data->player.pos_y][(int)new_x],
		(int)data->player.pos_y, (int)new_x))
		data->player.pos_x = new_x;
	if (valid_tile(data, data->map.maps[(int)new_y][(int)data->player.pos_x],
		(int)new_y, (int)data->player.pos_x))
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
		angle = -ROTSPEED;
	}
	else
		angle = ROTSPEED;
	data->player.dir_x = data->player.dir_x * cos(angle)
		- data->player.dir_y * sin(angle);
	data->player.dir_y = temp_dir_x * sin(angle)
		+ data->player.dir_y * cos(angle);
	data->player.plane_x = data->player.plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = temp_plane_x * sin(angle)
		+ data->player.plane_y * cos(angle);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:19 by vlow              #+#    #+#             */
/*   Updated: 2025/07/06 16:03:57 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"

void	init_doors(t_data *data)
{
	int	y;
	int	x;
	int	x_len;

	data->map.door_open = malloc(sizeof(int *) * (data->map.y_size + 1));
	data->map.door_open[data->map.y_size] = NULL;
	y = -1;
	while (++y < data->map.y_size)
	{
		x_len = ft_strlen(data->map.maps[y]);
		data->map.door_open[y] = malloc(sizeof(int) * x_len);
		x = -1;
		while (++x < x_len)
			data->map.door_open[y][x] = 0;
	}
}

void	try_toggle_door(t_data *data)
{
	double	try_dist;
	double	try_x;
	double	try_y;
	int		matrix[4];

	try_dist = 0.75;
	try_x = data->player.pos_x + data->player.dir_x * try_dist;
	try_y = data->player.pos_y + data->player.dir_y * try_dist;
	matrix[0] = (int)floor(try_x);
	matrix[1] = (int)floor(try_y);
	matrix[2] = (int)floor(data->player.pos_x);
	matrix[3] = (int)floor(data->player.pos_y);
	if (matrix[0] == matrix[2] && matrix[1] == matrix[3])
		return ;
	if (data->map.maps[matrix[1]][matrix[0]] == 'D')
	{
		data->map.door_open[matrix[1]][matrix[0]]
			= !data->map.door_open[matrix[1]][matrix[0]];
	}
}

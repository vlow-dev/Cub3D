/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:19 by vlow              #+#    #+#             */
/*   Updated: 2025/07/02 01:47:24 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

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

static int	*cell_player_matrix(double x, double y, t_data *data)
{
	int	*matrix;

	matrix = malloc(sizeof(int) * 4);
	matrix[0] = (int)floor(x);
	matrix[1] = (int)floor(y);
	matrix[2] = (int)floor(data->player.pos_x);
	matrix[3] = (int)floor(data->player.pos_y);
	return (matrix);
}

void	try_toggle_door(t_data *data)
{
	double	test_dist;
	double	test_x;
	double	test_y;
	int		*matrix;

	test_dist = 0.75;
	test_x = data->player.pos_x + data->player.dir_x * test_dist;
	test_y = data->player.pos_y + data->player.dir_y * test_dist;
	matrix = cell_player_matrix(test_x, test_y, data);
	if (matrix[0] == matrix[2] && matrix[1] == matrix[3])
		return ;
	if (data->map.maps[matrix[1]][matrix[0]] == '2')
	{
		data->map.door_open[matrix[1]][matrix[0]]
			= !data->map.door_open[matrix[1]][matrix[0]];
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:30:32 by vlow              #+#    #+#             */
/*   Updated: 2025/07/05 13:24:12 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"
#include "../../minilibx-linux/mlx.h"
#include <stdlib.h>

// ############################################################################
//									Free MLX
// ############################################################################
int	free_mlx(t_data *data)
{
	if (data->img.img)
	{
		mlx_destroy_image(data->vars.mlx, data->img.img);
		data->img.img = NULL;
	}
	if (data->vars.win)
	{
		mlx_destroy_window(data->vars.mlx, data->vars.win);
		data->vars.win = NULL;
	}
	if (data->vars.mlx)
	{
		mlx_destroy_display(data->vars.mlx);
		free(data->vars.mlx);
		data->vars.mlx = NULL;
	}
	return (1);
}

int	close_exit(t_data *data)
{
	split_free((void **)data->map.maps);
	split_free((void **)data->map.door_open);
	split_free((void **)data->compass.frame);
	split_free((void **)data->door.frame);
	for (int i = 0; i < TEX_SIZE; i++)
	{
		free(data->map.tex[i]);
		mlx_destroy_image(data->vars.mlx, data->tex[i].img);
	}
	for (int i = 0; i < COMPASS_FRAME; i++)
	{
		mlx_destroy_image(data->vars.mlx, data->c_frame[i].img);
	}
	///need to free other stuff
	free_mlx(data);
	exit(0);
}


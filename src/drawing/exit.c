/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:30:32 by vlow              #+#    #+#             */
/*   Updated: 2025/07/12 20:55:52 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"
#include "../../minilibx-linux/mlx.h"
#include <inttypes.h>
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

void	free_map_tex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEX_SIZE)
	{
		free(data->map.tex[i]);
		mlx_destroy_image(data->vars.mlx, data->tex[i].img);
	}
}

void	free_compass_tex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < COMPASS_FRAME)
	{
		mlx_destroy_image(data->vars.mlx, data->c_frame[i].img);
	}
}

int	close_exit(t_data *data)
{
	split_free((void **)data->map.maps);
	split_free((void **)data->map.door_open);
	split_free((void **)data->compass.frame);
	free_map_tex(data);
	free_compass_tex(data);
	free_mlx(data);
	exit(0);
}

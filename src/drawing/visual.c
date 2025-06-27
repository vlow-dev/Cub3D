/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:26 by vlow              #+#    #+#             */
/*   Updated: 2025/06/27 12:27:27 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"
#include "../../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>

void	init_tex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEX_SIZE)
	{
		ft_printf("Loading texture: %s\n", data->map.tex[i]);
		if (access(data->map.tex[i], R_OK) != 0)
			ft_printf("  → cannot access file: %s\n", strerror(errno));
		data->tex[i].img = mlx_xpm_file_to_image(data->vars.mlx,
				data->map.tex[i], &data->tex[i].x, &data->tex[i].y);
		if (!data->tex[i].img)
		{
			ft_printf("Error! Failed to initialize Tex IMG\n");
			close_exit(data);
		}
		data->tex[i].addr = mlx_get_data_addr(data->tex[i].img,
				&data->tex[i].bpp, &data->tex[i].line_len,
				&data->tex[i].endian);
		if (!data->tex[i].addr)
		{
			ft_printf("Error! Failed to initialize Tex Addr\n");
			close_exit(data);
		}
	}
}

void	init_compass_frame_tex(t_data *data)
{
	int	i;

	i = -1;
	data->compass.frame = ft_calloc(COMPASS_FRAME + 1, sizeof(char *));
	while (++i < COMPASS_FRAME)
	{
		data->compass.frame[i] = ft_strjoin_free(data->compass.frame[i],
				"textures/compass_frame/compass_", 0);
		data->compass.frame[i] = ft_strjoin_free(data->compass.frame[i],
				ft_itoa_pad(i, 2), 1);
		data->compass.frame[i] = ft_strjoin_free(data->compass.frame[i],
				".xpm", 0);
	}
}

void	init_compass_frame(t_data *data)
{
	int	i;

	i = -1;
	init_compass_frame_tex(data);
	while (++i < COMPASS_FRAME)
	{
		ft_printf("Loading compass frame: %s\n", data->compass.frame[i]);
		if (access(data->compass.frame[i], R_OK) != 0)
			ft_printf("  → cannot access file: %s\n", strerror(errno));
		data->c_frame[i].img = mlx_xpm_file_to_image(data->vars.mlx,
				data->compass.frame[i],
				&data->c_frame[i].x, &data->c_frame[i].y);
		data->c_frame[i].addr = mlx_get_data_addr(data->c_frame[i].img,
				&data->c_frame[i].bpp, &data->c_frame[i].line_len,
				&data->c_frame[i].endian);
		if (!data->c_frame[i].addr || !data->c_frame[i].img)
		{
			ft_printf("Error! Failed to initialize compass frame Addr\n");
			close_exit(data);
		}
	}
}

void	init_player(t_data *data)
{
	// this has to be based on the N,S,W,E symbols on map
	data->player.pos_x = 14 + 0.5;
	data->player.pos_y = 7 + 0.5;

	data->player.dir_x = 0;
	data->player.dir_y = -1;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0;

	// pSide = data->map.maps[y][x];
	//
	// if (pSide == 'N')
	// {
	// 	data->player.dir_x = 0;
	// 	data->player.dir_y = -1;
	// 	data->player.plane_x = 0.66;
	// 	data->player.plane_y = 0;
	// }
	// else if (pSide == 'S')
	// {
	// 	data->player.dir_x = 0;
	// 	data->player.dir_y = 1;
	// 	data->player.plane_x = -0.66;
	// 	data->player.plane_y = 0;
	// }
	// else if (pSide == 'W')
	// {
	// 	data->player.dir_x = -1;
	// 	data->player.dir_y = 0;
	// 	data->player.plane_x = 0;
	// 	data->player.plane_y = -0.66;
	// }
	// else if (pSide == 'E')
	// {
	// 	data->player.dir_x = 1;
	// 	data->player.dir_y = 0;
	// 	data->player.plane_x = 0;
	// 	data->player.plane_y = 0.66;
	// }
}


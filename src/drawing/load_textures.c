/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:26 by vlow              #+#    #+#             */
/*   Updated: 2025/07/06 17:27:08 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"
#include "../../minilibx-linux/mlx.h"
#include <X11/X.h>

static void	check_tex(t_data *data, int i)
{
	const char	*arr[] = {
		"NORTH", "SOUTH", "WEST", "EAST", "DOOR", NULL
	};

	if (access(data->map.tex[i], R_OK) != 0)
	{
		ft_printf("[%s] → cannot access file: %s\n", data->map.tex[i],
			strerror(errno));
		if (i < 0 || i > 4)
			return ;
		else if (i == 4)
		{
			data->map.tex[i] = ft_strdup("textures/default/wood_door.xpm");
			if (!data->map.tex[i])
				return ;
		}
		else if (i < 4)
		{
			data->map.tex[i] = ft_strdup("textures/default/wood.xpm");
			if (!data->map.tex[i])
				return ;
		}
		ft_printf("Setting to default: [%s:%s]\n", arr[i], data->map.tex[i]);
	}
}

void	init_tex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEX_SIZE)
	{
		check_tex(data, i);
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
				"textures/default/compass_frame/compass_", 0);
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
		if (access(data->compass.frame[i], R_OK) != 0)
			ft_printf("[%s] → cannot access file: %s\n", data->compass.frame[i],
				strerror(errno));
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

void	init_mlx(t_data *data)
{
	data->vars.mlx = mlx_init();
	if (!data->vars.mlx)
	{
		ft_printf("Error! Failed to initialize MLX\n");
		close_exit(data);
	}
	data->vars.win = mlx_new_window(data->vars.mlx, WIDTH, HEIGHT, "Womp Womp");
	if (!data->vars.win)
	{
		ft_printf("Error! Failed to initialize WIN\n");
		close_exit(data);
	}
	data->img.img = mlx_new_image(data->vars.mlx, WIDTH, HEIGHT);
	if (!data->img.img)
	{
		ft_printf("Error! Failed to initialize IMG\n");
		close_exit(data);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.addr)
	{
		ft_printf("Error! Failed to initialize IMG Addr\n");
		close_exit(data);
	}
}

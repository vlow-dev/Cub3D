/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:30:32 by vlow              #+#    #+#             */
/*   Updated: 2025/06/10 19:57:25 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdio.h>
#include <sys/time.h>


// ############################################################################
//									Parsing
// ############################################################################
void	test_map(t_data *data)
{
	static char *hardcoded_map[] = {
		"        1111111111111111111111111",
		"        1000000000110000000000001",
		"        1011000001110000000000001",
		"        1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001112111111111111",
		"11110111111111011100000010001",
		"1111011111111101 201010010001",
		"11000000110101011100000010001",
		"10000000000000001100000020001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL
	};

	int i;
	int len = ft_split_size(hardcoded_map);

	// Count how many lines
	// for (len = 0; hardcoded_map[len]; len++)
	// 	;

	// Allocate space for maps
	data->map.maps = malloc(sizeof(char *) * (len + 1));
	if (!data->map.maps)
		return ;

	// Copy lines
	for (i = 0; i < len; i++)
	{
		data->map.maps[i] = ft_strdup(hardcoded_map[i]);
		if (!data->map.maps[i])
		{
			ft_printf("Error test_map load\n");
			return ;
		}
	}
	data->map.maps[i] = NULL; // Null-terminate maps

	// just need a max x_size for minimap
	data->map.x_size = 33;
	data->map.y_size = len;
	// data->map.no = ft_strdup("textures/bluestone.xpm");
	// data->map.so = ft_strdup("textures/bluestone.xpm");
	// data->map.we = ft_strdup("textures/bluestone.xpm");
	// data->map.ea = ft_strdup("textures/bluestone.xpm");
	data->map.tex[TEX_NO] = ft_strdup("textures/wood.xpm");
	data->map.tex[TEX_SO] = ft_strdup("textures/wood.xpm");
	data->map.tex[TEX_WE] = ft_strdup("textures/wood.xpm");
	data->map.tex[TEX_EA] = ft_strdup("textures/wood.xpm");
	data->map.tex[TEX_DO] = ft_strdup("textures/door_frame/door_00.xpm");
	// data->compass.frame[0] = ft_strdup("textures/compass_frame/compass_00.xpm");
	// data->compass.frame[1] = ft_strdup("textures/compass_frame/compass_01.xpm");
	// data->compass.frame[2] = ft_strdup("textures/compass_frame/compass_02.xpm");
	// data->compass.frame[3] = ft_strdup("textures/compass_frame/compass_03.xpm");
	// data->compass.frame[4] = ft_strdup("textures/compass_frame/compass_04.xpm");
	// data->compass.frame[5] = ft_strdup("textures/compass_frame/compass_05.xpm");
	// data->compass.frame[6] = ft_strdup("textures/compass_frame/compass_06.xpm");
	// data->compass.frame[7] = ft_strdup("textures/compass_frame/compass_07.xpm");
	// data->compass.frame[8] = ft_strdup("textures/compass_frame/compass_08.xpm");
	// data->compass.frame[9] = ft_strdup("textures/compass_frame/compass_09.xpm");
	// data->compass.frame[10] = ft_strdup("textures/compass_frame/compass_10.xpm");
	// data->compass.frame[11] = ft_strdup("textures/compass_frame/compass_11.xpm");
	// data->compass.frame[12] = ft_strdup("textures/compass_frame/compass_12.xpm");
	// data->compass.frame[13] = ft_strdup("textures/compass_frame/compass_13.xpm");
	// data->compass.frame[14] = ft_strdup("textures/compass_frame/compass_14.xpm");
	// data->compass.frame[15] = ft_strdup("textures/compass_frame/compass_15.xpm");
	// data->compass.frame[16] = ft_strdup("textures/compass_frame/compass_16.xpm");
	// data->compass.frame[17] = ft_strdup("textures/compass_frame/compass_17.xpm");
	// data->compass.frame[18] = ft_strdup("textures/compass_frame/compass_18.xpm");
	// data->compass.frame[19] = ft_strdup("textures/compass_frame/compass_19.xpm");
	// data->compass.frame[20] = ft_strdup("textures/compass_frame/compass_20.xpm");
	// data->compass.frame[21] = ft_strdup("textures/compass_frame/compass_21.xpm");
	// data->compass.frame[22] = ft_strdup("textures/compass_frame/compass_22.xpm");
	// data->compass.frame[23] = ft_strdup("textures/compass_frame/compass_23.xpm");
	// data->compass.frame[24] = ft_strdup("textures/compass_frame/compass_24.xpm");
	// data->compass.frame[25] = ft_strdup("textures/compass_frame/compass_25.xpm");
	// data->compass.frame[26] = ft_strdup("textures/compass_frame/compass_26.xpm");
	// data->compass.frame[27] = ft_strdup("textures/compass_frame/compass_27.xpm");
	// data->compass.frame[28] = ft_strdup("textures/compass_frame/compass_28.xpm");
	data->map.floor = (220 << 16) | (100 << 8) | 0;
	data->map.ceiling = (225 << 16) | (30 << 8) | 0;
}

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
	// for (int i = 0; i < DOOR_FRAME; i++)
	// {
	// 	mlx_destroy_image(data->vars.mlx, data->d_frame[i].img);
	// }
	// free(data->map.no);
	// free(data->map.so);
	// free(data->map.we);
	// free(data->map.ea);
	///need to free other stuff
	free_mlx(data);
	exit(0);
}

void	init_mlx(t_data *data)
{
	data->vars.mlx = mlx_init();
	if (!data->vars.mlx)
	{
		ft_printf("Error! Failed to initialize MLX\n");
		close_exit(data);
	}
	data->vars.win = mlx_new_window(data->vars.mlx, WIDTH, HEIGHT, "Hello Cub3d");
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
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, \
									&data->img.line_len, &data->img.endian);
	if (!data->img.addr)
	{
		ft_printf("Error! Failed to initialize IMG Addr\n");
		close_exit(data);
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data data;
	
	ft_memset(&data, 0, sizeof(t_data));
	test_map(&data);
	init_mlx(&data);
	init_tex(&data);
	init_compass_frame(&data);
	init_player(&data);
	init_minimap(&data);
	init_doors(&data);
	mlx_put_image_to_window(data.vars.mlx, data.vars.win, data.img.img, 0, 0);
	mlx_hook(data.vars.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.vars.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_hook(data.vars.win, MotionNotify, PointerMotionMask, key_mouse, &data);
	mlx_mouse_move(data.vars.mlx, data.vars.win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(data.vars.mlx, data.vars.win);
	mlx_loop_hook(data.vars.mlx, reload_win, &data);
	mlx_hook(data.vars.win, DestroyNotify, 0, close_exit, &data);
	mlx_loop(data.vars.mlx);
	return (0);
}

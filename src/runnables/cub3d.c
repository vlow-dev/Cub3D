/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:41 by vlow              #+#    #+#             */
/*   Updated: 2025/07/06 17:29:27 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"
#include "../../minilibx-linux/mlx.h"
#include "parsing.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>
#include "stdlib.h"

void	init_fps(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->time.cur_time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->time.last_time_ms = data->time.cur_time_ms;
	data->time.st_time = data->time.cur_time_ms;
	data->time.delta_time = 0.0;
	data->time.fps_count = 0;
	data->time.fps = 0;
}

void	inits_modules(t_data *data)
{
	init_mlx(data);
	init_tex(data);
	init_compass_frame(data);
	init_player(data);
	init_minimap(data);
	init_doors(data);
	init_fps(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 2)
	{
		ft_printf_fd(2, "Syntax Error! usage: ./cub3d <path/to/map.cub\n");
		return (1);
	}
	if (!parse_map(&data, av[1]))
		return (1);
	inits_modules(&data);
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

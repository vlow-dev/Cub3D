/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:41 by vlow              #+#    #+#             */
/*   Updated: 2025/06/27 12:27:42 by vlow             ###   ########.fr       */
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

int	parse_map(t_data *data, char* av)
{
	t_result *res;

	res = parse_file(av);
	if (res->result == ERROR)
	{
		ft_printf_fd(2, "%s\n", res->data.err);
		free(res->data.err);
		return (0);
	}
	data->map = *(res->data.map);
	free(res->data.map);
	return (1);
}

void inits_modules(t_data *data)
{
	init_mlx(data);
	init_tex(data);
	init_compass_frame(data);
	init_player(data);
	init_minimap(data);
	init_doors(data);
}

int	main(int ac, char **av)
{
	t_data data;
	
	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 2)
	{
		ft_printf_fd(2, "Syntax Error! usage: ./cub3d <path/to/map.cub\n");
		return (1);
	}
	if (!parse_map(&data, av[1]))
		return (1);
	// test_map(&data);
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

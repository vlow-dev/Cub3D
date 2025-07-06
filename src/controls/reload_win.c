/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:36:02 by vlow              #+#    #+#             */
/*   Updated: 2025/07/06 16:09:30 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "../../minilibx-linux/mlx.h"
#include <sys/time.h>

static void	print_fps(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->time.cur_time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->time.delta_time = (data->time.cur_time_ms - data->time.last_time_ms)
		/ 1000.0;
	data->time.last_time_ms = data->time.cur_time_ms;
	data->time.fps_count++;
	if (data->time.cur_time_ms - data->time.st_time >= 1000)
	{
		data->time.fps = data->time.fps_count;
		ft_printf("FPS: %d\n", data->time.fps);
		data->time.fps_count = 0;
		data->time.st_time = data->time.cur_time_ms;
	}
}

int	reload_win(void *reload)
{
	t_data	*data;

	data = (t_data *)reload;
	print_fps(data);
	ft_bzero(data->img.addr, WIDTH * HEIGHT * (data->img.bpp / 8));
	move_key(data);
	raycasting(data);
	draw_minimap(data);
	draw_compass(data);
	mlx_put_image_to_window(data->vars.mlx, data->vars.win,
		data->img.img, 0, 0);
	return (0);
}

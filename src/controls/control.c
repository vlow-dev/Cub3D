/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:25 by vlow              #+#    #+#             */
/*   Updated: 2025/07/02 14:11:48 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../minilibx-linux/mlx.h"
#include "../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>

// ############################################################################
//								KeyHooks
// ############################################################################
void	move_key(t_data *data)
{
	if (data->player.key_w)
		w_key(data);
	if (data->player.key_s)
		s_key(data);
	if (data->player.key_a)
		a_key(data);
	if (data->player.key_d)
		d_key(data);
	if (data->player.key_left || data->player.key_right)
		lr_key(data);
}

void print_fps(t_data *data)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	data->time.cur_time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->time.delta_time = (data->time.cur_time_ms - data->time.last_time_ms) / 1000.0;
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

int	valid_tile(t_data *data, char tile, int y, int x)
{
	return ((tile == '0'
			|| tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
		|| (tile == '2'
			&& data->map.door_open[y][x] == 1));
}

int	key_press(int key, t_data *data)
{
	if (key == XK_w || key == XK_W)
		data->player.key_w = 1;
	if (key == XK_s || key == XK_S)
		data->player.key_s = 1;
	if (key == XK_a || key == XK_A)
		data->player.key_a = 1;
	if (key == XK_d || key == XK_D)
		data->player.key_d = 1;
	if (key == XK_Up)
		data->player.key_up = 1;
	if (key == XK_Down)
		data->player.key_down = 1;
	if (key == XK_Left)
		data->player.key_left = 1;
	if (key == XK_Right)
		data->player.key_right = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_w || key == XK_W)
		data->player.key_w = 0;
	if (key == XK_s || key == XK_S)
		data->player.key_s = 0;
	if (key == XK_a || key == XK_A)
		data->player.key_a = 0;
	if (key == XK_d || key == XK_D)
		data->player.key_d = 0;
	if (key == XK_e || key == XK_E)
		try_toggle_door(data);
	if (key == XK_Up)
		data->player.key_up = 0;
	if (key == XK_Down)
		data->player.key_down = 0;
	if (key == XK_Left)
		data->player.key_left = 0;
	if (key == XK_Right)
		data->player.key_right = 0;
	if (key == XK_Escape || key == XK_q)
		close_exit(data);
	return (0);
}

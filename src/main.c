/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:30:32 by vlow              #+#    #+#             */
/*   Updated: 2025/05/06 18:00:51 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdio.h>
#include <math.h>


// ############################################################################
//									Init Temp
// ############################################################################
void	test_map(t_data *data)
{
	static char *hardcoded_map[] = {
		"        1111111111111111111111111",
		"        1000000000110000000000001",
		"        1011000001110000000000001",
		"        1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL
	};

	int i;
	int len;

	// Count how many lines
	for (len = 0; hardcoded_map[len]; len++)
		;

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

	data->map.x_size = 33;
	data->map.y_size = len;
	data->map.no = ft_strdup("./path_to_the_north_texture");
	data->map.so = ft_strdup("./path_to_the_south_texture");
	data->map.we = ft_strdup("./path_to_the_west_texture");
	data->map.ea = ft_strdup("./path_to_the_east_texture");
	data->map.floor = (220 << 16) | (100 << 8) | 0;
	data->map.ceiling = (225 << 16) | (30 << 8) | 0;
}

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
	split_free(data->map.maps);
	free(data->map.no);
	free(data->map.so);
	free(data->map.we);
	free(data->map.ea);
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

int	ft_clamp(int a, int val)
{
	if (a < val)
		return (a);
	return (val);
}

double	ft_fclamp(double a, double val)
{
	if (a < val)
		return (a);
	return (val);
}

// ############################################################################
//								KeyHooks
// ############################################################################

void	draw_minimap(t_data *data);
void	draw_player(t_data *data);
void	else_key(t_data *data);
void	raycasting(t_data *data);

int	reload_win(void *reload)
{
	t_data *data;

	data = (t_data *)reload;
	ft_bzero(data->img.addr, WIDTH * HEIGHT * (data->img.bpp / 8));
	// load_line(data);
	else_key(data);
	// draw_player(data);
	raycasting(data);	//wip
	draw_minimap(data);
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, \
						data->img.img, 0, 0);
	// if (data->menu.flag)
	// 	print_menu(data);
	// else
	// 	print_smenu(data);
	return (0);
}

void	else_key(t_data *data)
{
    const double moveSpeed = 0.1;                       // how fast to move
    const double rotSpeed  = 5.0 * M_PI / 180.0;        // 5 degrees → radians
    double      newX, newY;
    double      oldDirX, oldPlaneX;

    // ─── MOVE FORWARD ───────────────────────────────────────
    if (data->player.key_w)
    {
        newX = data->player.pos_x + data->player.dir_x * moveSpeed;
        newY = data->player.pos_y + data->player.dir_y * moveSpeed;
        // X-axis collision check
        if (data->map.maps[(int)data->player.pos_y][(int)newX] == '0')
            data->player.pos_x = newX;
        // Y-axis collision check
        if (data->map.maps[(int)newY][(int)data->player.pos_x] == '0')
            data->player.pos_y = newY;
    }

    // ─── MOVE BACKWARD ──────────────────────────────────────
    if (data->player.key_s)
    {
        newX = data->player.pos_x - data->player.dir_x * moveSpeed;
        newY = data->player.pos_y - data->player.dir_y * moveSpeed;
        if (data->map.maps[(int)data->player.pos_y][(int)newX] == '0')
            data->player.pos_x = newX;
        if (data->map.maps[(int)newY][(int)data->player.pos_x] == '0')
            data->player.pos_y = newY;
    }

    // ─── MOVE LEFT ──────────────────────────────────────
    if (data->player.key_a)
    {
        newX = data->player.pos_x - data->player.plane_x * moveSpeed;
        newY = data->player.pos_y - data->player.plane_y * moveSpeed;
        if (data->map.maps[(int)data->player.pos_y][(int)newX] == '0')
            data->player.pos_x = newX;
        if (data->map.maps[(int)newY][(int)data->player.pos_x] == '0')
            data->player.pos_y = newY;
    }
    // ─── MOVE RIGHT ──────────────────────────────────────
    if (data->player.key_d)
    {
        newX = data->player.pos_x + data->player.plane_x * moveSpeed;
        newY = data->player.pos_y + data->player.plane_y * moveSpeed;
        if (data->map.maps[(int)data->player.pos_y][(int)newX] == '0')
            data->player.pos_x = newX;
        if (data->map.maps[(int)newY][(int)data->player.pos_x] == '0')
            data->player.pos_y = newY;
    }
    // ─── ROTATE LEFT / RIGHT ────────────────────────────────
    if (data->player.key_left || data->player.key_right)
    {
        // remember originals
        oldDirX    = data->player.dir_x;
        oldPlaneX  = data->player.plane_x;
        // choose rotation direction
        double angle = data->player.key_left ? -rotSpeed : rotSpeed;

        // rotate direction vector
        data->player.dir_x = data->player.dir_x * cos(angle)
                            - data->player.dir_y * sin(angle);
        data->player.dir_y = oldDirX * sin(angle)
                            + data->player.dir_y * cos(angle);

        // rotate camera plane
        data->player.plane_x = data->player.plane_x * cos(angle)
                              - data->player.plane_y * sin(angle);
        data->player.plane_y = oldPlaneX * sin(angle)
                              + data->player.plane_y * cos(angle);
    }
}

int	input_key(int key, t_data *data)
{
	if (key == XK_Escape || key == XK_q)
		close_exit(data);
	// if (data->key.ctrl)
	// 	ctrl_key(data, key);
	// else if (data->key.shift)
	// 	shift_key(data, key);
	// else if (data->key.alt)
	// 	alt_key(data, key);
	// else
	// 	else_key(data, key);
	// reload_win(data);
	return (0);
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

	// if (key == XK_Control_L || key == XK_Control_R)
	// 	data->key.ctrl = 1;
	// if (key == XK_Shift_L || key == XK_Shift_R)
	// 	data->key.shift = 1;
	// if (key == XK_Alt_L || key == XK_Alt_R)
	// 	data->key.alt = 1;
	input_key(key, data);
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
	if (key == XK_Up)
		data->player.key_up = 0;
	if (key == XK_Down)
		data->player.key_down = 0;
	if (key == XK_Left)
		data->player.key_left = 0;
	if (key == XK_Right)
		data->player.key_right = 0;
	// if (key == XK_Control_L || key == XK_Control_R)
	// 	data->key.ctrl = 0;
	// if (key == XK_Shift_L || key == XK_Shift_R)
	// 	data->key.shift = 0;
	// if (key == XK_Alt_L || key == XK_Alt_R)
	// 	data->key.alt = 0;
	return (0);
}

// ############################################################################
//								Image Stuffs
// ############################################################################

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->img.addr + (y * data->img.line_len + x \
			* (data->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_minimap_border(t_data *data)
{
	int	w;
	int	h;
	int	x;
	int	y;

	w = (int)(data->map.x_size * data->mini.scale);
	h = (int)(data->map.y_size * data->mini.scale);
	x = -1;
	while (++x < w)
	{
		my_pixel_put(data, x, 0, GREY);
		my_pixel_put(data, x, h - 1, GREY);
	}
	y = -1;
	while (++y < h)
	{
		my_pixel_put(data, 0, y, GREY);
		my_pixel_put(data, w - 1, y, GREY);
	}
}

void	minimap_center_player(t_data *data)
{
	double	w;
	double	h;

	w = (data->map.x_size * data->mini.scale);
	h = (data->map.y_size * data->mini.scale);
	data->mini.p_x = (data->player.pos_x * data->mini.z_scale);
	data->mini.p_y = (data->player.pos_y * data->mini.z_scale);
	data->mini.p_ox = (w * 0.5) - data->mini.p_x;
	data->mini.p_oy = (h * 0.5) - data->mini.p_y;
	// printf("11data->mini.p_ox = %f\n", data->mini.p_ox);
	// printf("11data->mini.p_oy = %f\n", data->mini.p_oy);
	// my_pixel_put(data, w / 2, h / 2, RED);
}

void draw_minimap_player(t_data *data)
{
    int w = (int)(data->map.x_size * data->mini.scale + 0.5);
    int h = (int)(data->map.y_size * data->mini.scale + 0.5);
	int y = -4;
	int	x;

	// ft_printf("w = [%d]\n", w);
	// ft_printf("h = [%d]\n", h);
	while (++y < 4)
	{
		x = -4;
		while (++x < 4)
		{
			my_pixel_put(data, x + w / 2, y + h / 2, RED);
		}
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	unsigned int color = WHITE;
	int w = (int)(data->map.x_size * data->mini.scale);
	int h = (int)(data->map.y_size * data->mini.scale);
	// printf("data->mini.scale = %f\n", data->mini.scale);
	// data->mini.scale *= 0.5;
	// printf("data->mini.scale22 = %f\n", data->mini.scale);
	
	minimap_center_player(data);
	y = -1;
	while (++y < data->map.y_size)
	{
		x = -1;
		while (++x < data->map.x_size)
		{
			if (data->map.maps[y][x] == '1')
				color = BLUE;
			else if (data->map.maps[y][x] == '0')
				color = WHITE;
			else
				color = 0;
			dy = -1;
			while (++dy < data->mini.z_scale - 1)
			{
				dx = -1;
				while (++dx < data->mini.z_scale - 1)
				{
					int tx = (int)((double)(x * data->mini.z_scale + dx + data->mini.p_ox) + 0.5);
					int	ty = (int)((double)(y * data->mini.z_scale + dy + data->mini.p_oy) + 0.5);
					if (tx > 0 && tx < w - 1 && ty > 0 && ty < h -1)
						my_pixel_put(data, tx, ty, color);
				}
			}

		}
	}
	draw_minimap_border(data);
	draw_minimap_player(data);
}

void	init_minimap(t_data *data)
{
	data->mini.scale_x = (WIDTH * MMAP_SIZE) / (double)data->map.x_size;
	data->mini.scale_y = (HEIGHT * MMAP_SIZE) / (double)data->map.y_size;
	data->mini.scale = fmin(data->mini.scale_x, data->mini.scale_y);
	data->mini.zoom_factor = 1.5;
	data->mini.z_scale = (int)(data->mini.scale * data->mini.zoom_factor) + 0.5;

}


// ############################################################################
//								Image Stuffs
// ############################################################################

static void draw_player_dir(t_data *data)
{
    int start_x = (int)(data->player.pos_x * data->mini.scale);
    int start_y = (int)(data->player.pos_y * data->mini.scale);
    int line_len = 1 * data->mini.scale; // 4 tiles length
    int end_x = start_x + (int)(data->player.dir_x * line_len);
    int end_y = start_y + (int)(data->player.dir_y * line_len);

    int dx = end_x - start_x;
    int dy = end_y - start_y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    double x_inc = (double)dx / (double)steps;
    double y_inc = (double)dy / (double)steps;

    double x = start_x;
    double y = start_y;

    int i = 0;
    while (i <= steps)
    {
        my_pixel_put(data, (int)x, (int)y, RED);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

void	draw_player(t_data *data)
{
	int	p_size = 8 / 2;
	int	x;
	int y;
    int px = (int)(data->player.pos_x * data->mini.scale + data->mini.p_ox + 0.5);
    int py = (int)(data->player.pos_y * data->mini.scale + data->mini.p_oy + 0.5);

	y = -p_size - 1;
	while (++y < p_size)
	{
		x = -p_size - 1;
		while (++x < p_size)
		{
			my_pixel_put(data, px, py, RED);
			// my_pixel_put(data, (int)(data->player.pos_x * data->mini.scale) + x, (int)(data->player.pos_y * data->mini.scale) + y, RED);
		}
	}
	draw_player_dir(data);
}

void	init_player(t_data *data)
{
	data->player.pos_x = 14;
	data->player.pos_y = 7;

	// data->player.pos_x = (double)ft_strlen(data->map.maps[data->map.y_size / 2]) / 2.0 + 0.5;
	// data->player.pos_y = (double)data->map.y_size / 2.0 + 0.5;
	// printf("data->player.pos_x = %f\n", data->player.pos_x);
	// printf("data->player.pos_y = %f\n", data->player.pos_y);
	
	// player dir will need to be initialize based on map later on;
	// data->player.angle = 270.0;
	// data->player.dir_x = cos(data->player.angle * M_PI / 180.0);
	// data->player.dir_y = sin(data->player.angle * M_PI / 180.0);
	
	data->player.dir_x = 0;
	data->player.dir_y = -1;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0;
}

// ############################################################################
//								Ray Casting
// ############################################################################

void draw_minimap_ray(t_data *data)
{
    // 1) Player’s pixel on the minimap
    int start_x = (int)((data->player.pos_x * data->mini.z_scale) + data->mini.p_ox);
    int start_y = (int)((data->player.pos_y * data->mini.z_scale) + data->mini.p_oy);
    // int start_x = (int)(data->map.x_size * data->mini.scale);
    // int start_y = (int)(data->map.y_size * data->mini.scale);
    // int start_x = (int)(data->mini.p_ox);
    // int start_y = (int)(data->mini.p_oy);
	// printf("start_x = %d\n", start_x);
	// printf("start_y = %d\n", start_y);
	// printf("data->mini.p_ox = %f\n", data->mini.p_ox);
	// printf("data->mini.p_oy = %f\n", data->mini.p_oy);

    // 2) Compute exact hit point in world-space
    double hitX = data->player.pos_x + (ft_fclamp(data->ray.perpDist, sqrt((data->map.x_size * 0.25) + (data->map.y_size * 0.25)))) * data->ray.x;
    double hitY = data->player.pos_y + (ft_fclamp(data->ray.perpDist, sqrt((data->map.x_size * 0.25) + (data->map.y_size * 0.25)))) * data->ray.y;

	// 3) Convert hit point to minimap pixels
	int end_x = (int)(hitX * data->mini.z_scale) + data->mini.p_ox;
	int end_y = (int)(hitY * data->mini.z_scale) + data->mini.p_oy;

	// 4) DDA-style line from start → end
	int dx    = end_x - start_x;
	int dy    = end_y - start_y;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	double xi = dx / (double)steps;
	double yi = dy / (double)steps;
	double x  = start_x;
	double y  = start_y;

	for (int i = 0; i <= steps; i++)
	{
		my_pixel_put(data, (int)x, (int)y, SEMI_GREEN);
		x += xi;
        y += yi;
    }
}

void	raycasting(t_data *data)
{
	int ray = -1;

	while (++ray < WIDTH)
	{
		data->ray.cam_x = 2.0 * ray / (double)WIDTH - 1.0;

		data->ray.x = data->player.dir_x + (data->player.plane_x * data->ray.cam_x);
		data->ray.y = data->player.dir_y + (data->player.plane_y * data->ray.cam_x);

		// data->ray.dist_x = sqrt(1.0 + (data->ray.y /data->ray.x) * (data->ray.y / data->ray.x));
		// data->ray.dist_y = sqrt(1.0 + (data->ray.x /data->ray.y) * (data->ray.x / data->ray.y));
		data->ray.dist_x = fabs(1.0 / data->ray.x);
		data->ray.dist_y = fabs(1.0 / data->ray.y);
		
		data->ray.tile_x = (int)data->player.pos_x;
		data->ray.tile_y = (int)data->player.pos_y;

		if (data->ray.x < 0)
		{
			data->ray.side_x = -1;
			data->ray.len_x = (data->player.pos_x - data->ray.tile_x) * data->ray.dist_x;
		}
		else
		{
			data->ray.side_x = 1;
			data->ray.len_x = ((data->ray.tile_x + 1.0) - data->player.pos_x) * data->ray.dist_x;
		}

		if (data->ray.y < 0)
		{
			data->ray.side_y = -1;
			data->ray.len_y = (data->player.pos_y - data->ray.tile_y) * data->ray.dist_y;
		}
		else
		{
			data->ray.side_y = 1;
			data->ray.len_y = ((data->ray.tile_y + 1.0) - data->player.pos_y) * data->ray.dist_y;
		}
	
		int side;
		while (1)
		{
			if (data->ray.len_x < data->ray.len_y)
			{
				data->ray.len_x += data->ray.dist_x;
				data->ray.tile_x += data->ray.side_x;
				side = 0;
			}
			else
			{
				data->ray.len_y += data->ray.dist_y;
				data->ray.tile_y += data->ray.side_y;
				side = 1;
			}
			
			if (data->map.maps[data->ray.tile_y][data->ray.tile_x] > '0')
				break ;
		}
		if (side == 0)
			data->ray.perpDist = (data->ray.tile_x - data->player.pos_x
						+ (1 - data->ray.side_x) / 2.0)
					   / data->ray.x;
		else
			data->ray.perpDist = (data->ray.tile_y - data->player.pos_y
						+ (1 - data->ray.side_y) / 2.0)
					   / data->ray.y;

		int lineheight = (int)(HEIGHT / data->ray.perpDist);
		int drawStart = -lineheight / 2 + HEIGHT / 2;
		if (drawStart < 0 )
			drawStart = 0;
		int drawEnd = lineheight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		// draw the 3D slice:
		for (int y = 0; y < HEIGHT; y++) {
			if (y < drawStart)
				my_pixel_put(data, ray, y, YELLOW);
			else if (y <= drawEnd) {
				int color = (side == 1)
					? N_ORGE
					: GREY;
				my_pixel_put(data, ray, y, color);
			}
			else
			my_pixel_put(data, ray, y, PURPLE);
		}
		draw_minimap_ray(data);

	}
}

// void	raycasting(t_data *data)
// {
// 	int	ray;
// 	int	dof;
// 	int	mx;
// 	int	my;
// 	// int mp;
// 	float	step;
// 	// float dis_v
// 	// float dis_y;
//
// 	data->ray.angle = 30.0;
// 	ray = -1;
// 	while (++ray < 1)
// 	{
// 		dof = 0;
// 		step = tan(data->ray.angle * M_PI / 180.0);
// 		if (cos(data->ray.angle * M_PI / 180.0) > 0.001)
// 		{
// 			data->ray.x = (((int)data->player.pos_x >> 6) << 6) + 64;
// 			data->ray.y = (data->player.pos_x - data->ray.x) * step + data->player.pos_y;
// 			data->ray.ox = 64;
// 			data->ray.oy = -data->ray.ox * step;
// 		}
// 		else if (cos(data->ray.angle * M_PI / 180.0) < -0.001)
// 		{
// 			data->ray.x = (((int)data->player.pos_x >> 6) << 6) - 0.0001;
// 			data->ray.y = (data->player.pos_x - data->ray.x) * step + data->player.pos_y;
// 			data->ray.ox = -64;
// 			data->ray.oy = -data->ray.ox * step;
// 		}
// 		else
// 		{
// 			data->ray.x = data->player.pos_x;
// 			data->ray.y = data->player.pos_y;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int)(data->ray.x) >> 6;
// 			my = (int)(data->ray.y) >> 6;
// 			if (mx >= 0 && mx < (int)ft_strlen(data->map.maps[my]) &&
// 				my >= 0 && my < data->map.y_size &&
// 				data->map.maps[my][mx] == '1')
// 			{
// 				dof = 8;
// 				// dis_v = cos((data->ray.angle - data->player.angle) * M_PI / 180.0) * (data->ray.x - data->player.pos_x) - sin((data->ray.angle - data->player.angle) * M_PI / 180.0) * (data->ray.y - data->player.pos_y);
// 			}
// 			else
// 			{
// 				data->ray.x += data->ray.ox;
// 				data->ray.y += data->ray.oy;
// 				dof += 1;
// 			}
// 		}
// 	}
// 	draw_ray_line(data, data->ray.x, data->ray.y);
//
// }

// ############################################################################
//								Main
// ############################################################################

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data data;
	
	ft_memset(&data, 0, sizeof(t_data));
	test_map(&data);
	init_mlx(&data);
	init_player(&data);
	init_minimap(&data);


	mlx_put_image_to_window(data.vars.mlx, data.vars.win, data.img.img, 0, 0);
	reload_win(&data);
	mlx_hook(data.vars.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.vars.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_loop_hook(data.vars.mlx, reload_win, &data);
	mlx_hook(data.vars.win, DestroyNotify, 0, close_exit, &data);
	mlx_loop(data.vars.mlx);
	// close_exit(&data);
	// int	i;
	//
	// i = 0;
	// while (++i < ac)
	// 	ft_printf("av[%d] = [%s]\n", i, av[i]);
	return (0);
}

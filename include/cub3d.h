/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:31:23 by vlow              #+#    #+#             */
/*   Updated: 2025/07/12 20:28:30 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// WINDOWS
# define WIDTH 1920
# define HEIGHT 1080

// TEXTURES
# define TEX_SIZE 5
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_DO 4
# define COMPASS_FRAME 29

// MINIMAPS
# define MM_WALL     0x00404040
# define MM_FLOOR    0x00AAAAAA
# define MM_DOOR_C   0x00B22222
# define MM_DOOR_O   0x0000FF00
# define MM_PLAYER   0x00FF0000
# define MM_VIEW     0x0000FF00
# define MM_BORDER   0x80808080
# define MM_BASE	 0x00FFFFFF
# define MMAP_SIZE 0.4
# define MMAP_RADIUS 125
# define MMAP_MARGIN 10

// PLAYER MOVEMENT
# define MOUSESENS	0.0003
# define MOVESPEED	2.0
# define ROTSPEED	M_PI
# define ANISPEED	0.1

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
}	t_img;

typedef struct s_player_pos
{
	int		x;
	int		y;
	char	dir;
}	t_player_pos;

typedef struct s_map
{
	char				**maps;
	char				*tex[TEX_SIZE];
	unsigned int		floor;
	unsigned int		ceiling;
	int					y_size;
	int					x_size;
	int					**door_open;
	t_player_pos		pp;
}	t_map;

typedef struct s_ani
{
	char	**frame;
	int		idx;
	double	timer;
}	t_ani;

typedef struct s_minimap
{
	double		scale_x;
	double		scale_y;
	double		scale;
	double		zoom_factor;
	int			z_scale;
	double		p_x;
	double		p_y;
	double		p_ox;
	double		p_oy;
}	t_minimap;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		key_e;
}	t_player;

typedef struct s_ray
{
	int		tile_x;
	int		tile_y;
	double	cam_x;
	double	x;
	double	y;
	double	dist_x;
	double	dist_y;
	double	side_x;
	double	side_y;
	double	len_x;
	double	len_y;
	double	perp_dist;
	int		door;
}	t_ray;

typedef struct s_draw
{
	int		height;
	int		start;
	int		end;
	int		tex_side;
	int		tex_x;
	double	wall_x;
}	t_draw;

typedef struct s_time
{
	int		fps_count;
	int		fps;
	long	st_time;
	long	cur_time_ms;
	long	last_time_ms;
	double	delta_time;
}	t_time;

typedef struct s_data
{
	t_vars		vars;
	t_img		img;
	t_img		tex[TEX_SIZE];
	t_ani		compass;
	t_img		c_frame[COMPASS_FRAME];
	t_map		map;
	t_minimap	mini;
	t_player	player;
	t_ray		ray;
	t_draw		draw;
	t_time		time;
}	t_data;

//drawing
void	init_mlx(t_data *data);
void	my_pixel_put(t_data *data, int x, int y, int color);
void	draw_compass(t_data *data);
void	init_minimap(t_data *data);
void	init_doors(t_data *data);
void	init_tex(t_data *data);
void	init_compass_frame(t_data *data);
void	init_player(t_data *data);
void	draw_minimap(t_data *data);
void	raycasting(t_data *data);
void	draw_minimap_circle_border(t_data *data);
void	minimap_center_player(t_data *data);
void	draw_minimap_player(t_data *data);

// raycasting
void	ray_tex_init(t_data *data);
void	ray_tex_door(t_data *data, int side);
void	ray_tex_sides(t_data *data, int side);
void	ray_tex_draw(t_data *data, int ray);

//cleanup
int		close_exit(t_data *data);

//controls
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		key_mouse(int x, int y, t_data *data);
int		reload_win(void *reload);
void	lr_key(t_data *data);
void	d_key(t_data *data);
void	a_key(t_data *data);
void	s_key(t_data *data);
void	w_key(t_data *data);
void	move_key(t_data *data);
int		valid_tile(t_data *data, double y, double x);
void	try_toggle_door(t_data *data);

#endif

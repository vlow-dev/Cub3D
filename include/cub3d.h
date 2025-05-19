/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:31:23 by vlow              #+#    #+#             */
/*   Updated: 2025/05/14 16:17:53 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Window size
# define WIDTH 1920
# define HEIGHT 1080
# define TEX_SIZE 5
# define MMAP_SIZE 0.4
# define MMAP_RADIUS 125
# define MMAP_MARGIN 10
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_DO 4

//color
# define RED	0x00FF0000
# define ORANGE	0x00FFA500
# define YELLOW	0x00FFFF00
# define GREEN	0x0000FF00
# define SEMI_GREEN 0x00BFFFBF
# define CYAN	0x0000FFFF
# define BLUE	0x000000FF
# define PURPLE	0x00800080
# define WHITE	0x00FFFFFF
# define BLACK	0x00000000
# define GREY	0x80808080
# define M_CYAN	0x0066FFFF
# define T_GREY	0x00CCCCCC
# define N_ORGE	0x00FFA07A
# define HIGH_COLOUR	RED
# define LOW_COLOUR		BLUE
# define TEXT_COLOR		T_GREY
# define MENU_COLOR		M_CYAN
# define NB_COLOR		N_ORGE

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

typedef struct s_map
{
	char				**maps;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*tex[TEX_SIZE];
	unsigned int		floor;
	unsigned int		ceiling;
	int					y_size;
	int					x_size;
}	t_map;

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
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		key_e;

}	t_player;

typedef struct s_ray
{
	// int	count;
	// int	dof;
	int		tile_x;
	int		tile_y;
	double	cam_x;
	double	x;
	double	y;
	// double	angle;
	// double	ox;
	// double	oy;
	double	dist_x;
	double	dist_y;
	double	side_x;
	double	side_y;
	double	len_x;
	double	len_y;
	double	perpDist;
	int		door;
	// double	door_state[];
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

typedef struct s_data
{
	t_vars	vars;
	t_img	img;
	t_img	tex[TEX_SIZE];
	t_map	map;
	t_minimap	mini;
	t_player	player;
	t_ray		ray;
	t_draw		draw;
}	t_data;

#endif

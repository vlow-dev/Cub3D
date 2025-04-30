/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:31:23 by vlow              #+#    #+#             */
/*   Updated: 2025/04/29 16:14:10 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Window size
# define WIDTH 1920
# define HEIGHT 1080
# define TEX_SIZE 64
# define MMAP_SIZE 32

//color
# define RED	0x00FF0000
# define ORANGE	0x00FFA500
# define YELLOW	0x00FFFF00
# define GREEN	0x0000FF00
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
# define P_FRONT 1
# define P_BACK 2
# define P_LEFT 3
# define P_RIGHT 4
# define P_TOP 5
# define P_BOTTOM 6

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
}	t_img;

typedef struct s_map
{
	char				**maps;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	unsigned int		floor;
	unsigned int		ceiling;
	int					y_size;
}	t_map;

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

}	t_player;

typedef struct s_ray
{
	int	count;
	int	dof;
	float	x;
	float	y;
	float	angle;
	float	ox;
	float	oy;
}	t_ray;

typedef struct s_data
{
	t_vars	vars;
	t_img	img;
	t_map	map;
	t_player	player;
	t_ray		ray;
}	t_data;

#endif

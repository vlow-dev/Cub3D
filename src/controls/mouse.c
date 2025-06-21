#include "../../include/cub3d.h"
#include <X11/keysym.h>
#include "../../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <math.h>
#include <sys/time.h>

void	rotate_player(t_data *data, double angle)
{
	double	temp_dir_x;
	double	temp_plane_x;

	temp_dir_x = data->player.dir_x;
	temp_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(angle)
		- data->player.dir_y * sin(angle);
	data->player.dir_y = temp_dir_x * sin(angle)
		+ data->player.dir_y * cos(angle);
	data->player.plane_x = data->player.plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = temp_plane_x * sin(angle)
		+ data->player.plane_y * cos(angle);
}

int	key_mouse(int x, int y, t_data *data)
{
	double	rot_speed;
	int		dx;

	(void)y;
	dx = x - (WIDTH / 2);
	if (dx != 0)
	{
		rot_speed = dx * 0.0003;
		rotate_player(data, rot_speed);
		mlx_mouse_move(data->vars.mlx, data->vars.win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

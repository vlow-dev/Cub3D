#include "../../libft/include/libft.h"
#include "../../include/cub3d.h"
#include "../../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
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

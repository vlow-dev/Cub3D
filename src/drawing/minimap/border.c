/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:49 by vlow              #+#    #+#             */
/*   Updated: 2025/07/05 16:39:02 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <sys/time.h>

static void	actual_draw(int cx, int cy, int *axises, t_data *data)
{
	my_pixel_put(data, cx + axises[2], cy + axises[3], GREY);
	my_pixel_put(data, cx + axises[3], cy + axises[2], GREY);
	my_pixel_put(data, cx - axises[3], cy + axises[2], GREY);
	my_pixel_put(data, cx - axises[2], cy + axises[3], GREY);
	my_pixel_put(data, cx - axises[2], cy - axises[3], GREY);
	my_pixel_put(data, cx - axises[3], cy - axises[2], GREY);
	my_pixel_put(data, cx + axises[3], cy - axises[2], GREY);
	my_pixel_put(data, cx + axises[2], cy - axises[3], GREY);
}

// 5 here represent thickness bro
// int i; //0
// int r; //1
// int x;//2
// int y;//3
// int err; //4
void	draw_loop(int cx, int cy, int outer_r, t_data *data)
{
	int	axises[5];

	axises[0] = -1;
	while (++(axises[0]) < 4)
	{
		axises[1] = outer_r - axises[0];
		axises[2] = axises[1];
		axises[3] = 0;
		axises[4] = 1 - axises[1];
		while (axises[2] >= axises[3])
		{
			actual_draw(cx, cy, axises, data);
			axises[3]++;
			if (axises[4] < 0)
				axises[4] += 2 * axises[3] + 1;
			else
			{
				axises[2]--;
				axises[4] += 2 * (axises[3] - axises[2]) + 1;
			}
		}
	}
}

void	draw_minimap_circle_border(t_data *data)
{
	int	cx;
	int	cy;
	int	outer_r;

	cx = MMAP_RADIUS + MMAP_MARGIN;
	cy = MMAP_RADIUS + MMAP_MARGIN;
	outer_r = MMAP_RADIUS;
	draw_loop(cx, cy, outer_r, data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:34 by ialee             #+#    #+#             */
/*   Updated: 2025/06/27 15:28:29 by ialee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/cub3d.h"
#include "libft.h"
#include <stdlib.h>

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	init_pp(t_player_pos **pp, int y, int x, char dir)
{
	(*pp) = malloc(sizeof(t_player_pos));
	(*pp)->y = y;
	(*pp)->x = x;
	(*pp)->dir = dir;
}

static t_player_pos	*get_pp(char **map)
{
	int				i;
	int				j;
	int				width;
	t_player_pos	*pp;

	i = 0;
	j = 0;
	pp = NULL;
	while (map[i])
	{
		width = safe_strlen(map[i]);
		j = 0;
		while (j < width)
		{
			if (is_player_char(map[i][j]))
			{
				init_pp(&pp, i, j, map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (pp);
}

int	parse_map(t_data *data, char *av)
{
	t_result	*res;

	res = get_map(av);
	if (res->result == ERROR)
	{
		ft_printf_fd(2, "%s\n", res->data.err);
		free(res->data.err);
		free(res);
		return (0);
	}
	data->map = *(res->data.map);
	free(res->data.map);
	free(res);
	return (1);
}

t_result	*get_map(char *path)
{
	t_map		*m;
	t_result	*file;

	file = parse_file(path);
	if (file->result == OK)
		m = file->data.map;
	else
	{
		return (file);
	}
	free(file);
	if (!is_map_valid(m))
	{
		free_map(m);
		return (result_error("Invalid map received"));
	}
	m->pp = get_pp(m->maps);
	if (m->pp == NULL)
	{
		free_map(m);
		return (result_error("Map with no player received"));
	}
	return (result_ok(&m));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:34 by ialee             #+#    #+#             */
/*   Updated: 2025/07/12 21:19:06 by vlow             ###   ########.fr       */
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

static int	get_pp(t_map *m)
{
	int				i;
	int				j;
	int				width;

	i = 0;
	while (m->maps[i])
	{
		width = safe_strlen(m->maps[i]);
		j = 0;
		while (j < width)
		{
			if (is_player_char(m->maps[i][j]))
			{
				m->pp.dir = m->maps[i][j];
				m->pp.x = j;
				m->pp.y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
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
	if (!get_pp(m))
	{
		free_map(m);
		return (result_error("Map with no player received"));
	}
	return (result_ok(&m));
}

#include "cub3d.h"
#include "parsing.h"

static void	vget_map_values(char **s, int fd)
{
	char	*str;
	int		y;

	y = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (is_map(str))
		{
			s[y] = str;
			y++;
		}
		str = get_next_line(fd);
	}
}

static char	**get_raw_map(t_unvalidated_map *m, char *file)
{
	int		fd;
	char	**ret;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error opening file\n", 2);
		exit(1);
	}
	ret = malloc(sizeof(char *) * (m->y_size + 1));
	ret[m->y_size] = NULL;
	vget_map_values(ret, fd);
	close (fd);
	return (ret);
}

static void	get_player(t_map *m)
{
	int				x;
	int				y;

	x = 0;
	y = 0;
	m->pp = malloc(sizeof(t_player_pos));
	while (x < m->x_size)
	{
		while (y < ft_strlen(m->maps[x]))
		{
			if (is_player(m->maps[x][y]))
			{
				m->pp->dir = m->maps[x][y];
				m->pp->x = x;
				m->pp->y = y;
				return ;
			}
		}
	}
	free(m->pp);
	m->pp = NULL;
}

void	extract_validated(t_map *map, t_unvalidated_map* m, char *file)
{
	map->maps = get_raw_map(m, file);
	get_player(map);
	if (m->pp == NULL)
		exit(-1);
}

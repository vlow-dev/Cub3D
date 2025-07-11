#include "cub3d.h"
#include "parsing.h"

// fc = floor/ceiling
void	get_color_value(char *str, int *fc, char **is_err)
{
	char	**split;
	int		rgb[3];

	is_valid_color(str, is_err);
	if (ft_strlen(*is_err) != 0)
		return ;
	split = ft_split(str, ',');
	if (split == NULL)
	{
		*is_err = ft_strdup("Error splitting str.");
		return ;
	}
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	ft_free_split(split);
	is_valid_color_range((int *)rgb, is_err)
	if (ft_strlen(*is_err) != 0)
		return ;
	*fc = ((rgb[0] & 0xff) << 16) | ((rgb[1] & 0xff) << 8)
		| (rgb[2] & 0xff);
}

void	set_color(char *str, t_map *map, char **is_err)
{
	static int	floor;
	static int	ceiling;

	while (ft_isspace(*str) == 1)
		str++;
	if (ft_strncmp(str, "C", 1) == 0 && ft_isspace(*(str + 1)) == 1)
	{
		if (ceiling == 0)
		{
			get_color_value(str + 1, &map->ceiling, is_err);
			ceiling++;
		}
		else
			*is_err = ft_strdup("Ceiling duplicate\n");
	}
	else if (ft_strncmp(str, "F", 1) == 0 && ft_isspace(*(str + 1)) == 1)
	{
		if (floor++ == 0)
		{
			get_color_value(str + 1, &map->floor, is_err);
			floor++;
		}
		else
			*is_err = ft_strdup("Floor duplicate\n");
	}
}

static bool	is_color(char *str)
{
	while (ft_isspace(*str) == 1)
		str++;
	return (ft_strncmp(str, "C", 1) == 0 || ft_strncmp(str, "F", 1) == 0);
}

void	get_color_data(t_map *map, int fd, char **is_err)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if (is_color(str))
		{
			set_color(str, map, is_err);
			if (ft_strlen(is_err) != 0)
			{
				while (str != NULL)
				{
					free(str);
					str = get_next_line(fd);
				}
				free_map(map);
				ft_putstr(is_err, 2);
				free(is_err);
				exit(1);
			}
		}
		free(str);
		str = get_next_line(fd);
	}
}

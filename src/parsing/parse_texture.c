#include "cub3d.h"
#include "parsing.h"

void	get_texture_path(char *str, char **path_store, char **is_err)
{
	if (!is_valid_texture(str, is_err))
		return ;
	while (ft_isspace(*str) == 1)
		str++;
	*path_store = ft_strdup(str);
	if (*path_store == NULL)
	{
		*is_err = ft_strdup("Failed to extract texture path\n");
	}
}

void	set_texture(char *str, t_map *map, char **is_err)
{
	while (ft_isspace(*str) == 1)
		str++;
	if (ft_strncmp(str, "NO", 2) == 0 && ft_isspace(*(str + 2)) == 1)
		get_texture_path(str + 2, map->tex[TEX_NO], is_err);
	else if (ft_strncmp(str, "SO", 2) == 0 && ft_isspace(*(str + 2)) == 1)
		get_texture_path(str + 2, map->tex[TEX_SO], is_err);
	else if (ft_strncmp(str, "EA", 2) == 0 && ft_isspace(*(str + 2)) == 1)
		get_texture_path(str + 2, map->tex[TEX_EA], is_err);
	else if (ft_strncmp(str, "WE", 2) == 0 && ft_isspace(*(str + 2)) == 1)
		get_texture_path(str + 2, map->tex[TEX_WE], is_err);
	else if (ft_strncmp(str, "DO", 2) == 0 && ft_isspace(*(str + 2)) == 1)
		get_texture_path(str + 2, map->tex[TEX_DO], is_err);
}

bool	is_texture(char *str)
{
	while (ft_isspace(*str) == 1)
		str++;
	if (ft_strncmp(str, "NO", 2) == 0
		|| ft_strncmp(str, "SO", 2) == 0
		|| ft_strncmp(str, "WE", 2) == 0
		|| ft_strncmp(str, "EA", 2) == 0
		|| ft_strncmp(str, "DO", 2) == 0)
		return (true);
	return (false);
}

void	get_texture_data(t_map *map, int fd, char **is_err)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if (is_texture(str) == true)
		{
			set_texture(str, map, is_err);
			if (ft_strlen(is_err) != 0)
			{
				while (str != NULL)
				{
					free(str);
					str = get_next_line(fd);
				}
				free_map(map);
				ft_putstr_fd(is_err, 2);
				free(is_err);
				exit(1);
			}
		}
		free(str);
		str = get_next_line(fd);
	}
}

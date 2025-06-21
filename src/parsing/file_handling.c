#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"
#include "../../include/parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

static void	get_lines(t_list **lines, char **tmp, int fd)
{
	while (*tmp)
	{
		free(*tmp);
		*tmp = get_next_line(fd);
		if (tmp)
			ft_lstadd_back(&(*lines), ft_lstnew(ft_strdup(*tmp)));
	}
}

static char	**extract_file(char *file_path)
{
	int		fd[2];
	t_list	*lines;
	char	*tmp;
	char	**ret;
	t_list	*itr;

	fd[0] = open(file_path, O_RDONLY);
	tmp = get_next_line(fd[0]);
	lines = ft_lstnew(ft_strdup(tmp));
	get_lines(&lines, &tmp, fd[0]);
	ret = malloc(sizeof(char *) * (ft_lstsize(lines) + 1));
	fd[1] = 0;
	itr = lines;
	while (itr)
	{
		ret[fd[1]++] = (char *)itr->content;
		itr = itr->next;
	}
	ret[fd[1]] = NULL;
	ft_lstclear(&lines, NULL);
	return (ret);
}

static int	extract_info(t_map **map, char **raw_file)
{
	int	line_idx;

	line_idx = 0;
	while (raw_file[line_idx][0] != '1')
	{
		if (!raw_file[line_idx])
			return (-1);
		if (ft_strncmp("NO", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_NO] = get_path_direction(raw_file[line_idx]);
		else if (ft_strncmp("SO", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_SO] = get_path_direction(raw_file[line_idx]);
		else if (ft_strncmp("WE", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_WE] = get_path_direction(raw_file[line_idx]);
		else if (ft_strncmp("EA", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_EA] = get_path_direction(raw_file[line_idx]);
		else if (raw_file[line_idx][0] == 'F')
			(*map)->floor = get_colours(raw_file[line_idx]);
		else if (raw_file[line_idx][0] == 'C')
			(*map)->ceiling = get_colours(raw_file[line_idx]);
		line_idx++;
	}
	return (line_idx);
}

static t_result	*handle_map(t_map **map, char **raw_file, int line_idx)
{
	int	size;

	if (line_idx == -1)
		return (result_error("invalid .cub file."));
	size = line_idx;
	while (raw_file[size])
		size++;
	(*map)->y_size = (size - line_idx);
	(*map)->maps = malloc(sizeof(char *) * (*map)->y_size + 1);
	size = 0;
	while (raw_file[line_idx])
		(*map)->maps[size++] = ft_strdup(raw_file[line_idx++]);
	(*map)->maps[size] = NULL;
	return (result_ok(*map));
}

t_result	*parse_file(char *file_path)
{
	t_map		*map;
	char		**raw_file;
	t_result	*res;
	int			leng;

	leng = ft_strlen(file_path);
	if (ft_strlen(file_path) <= 4
		|| ft_strncmp(".cub", &file_path[leng - 4], 4))
		return (result_error("file provided is not a .cub file"));
	res = malloc(sizeof(t_result));
	map = malloc(sizeof(t_map));
	raw_file = extract_file(file_path);
	extract_info(&map, raw_file);
	res = handle_map(&map, raw_file, extract_info(&map, raw_file));
	return (res);
}

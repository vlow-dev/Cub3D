/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:31 by vlow              #+#    #+#             */
/*   Updated: 2025/06/27 15:30:52 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"
#include "../../include/parsing.h"
#include <stdlib.h>
// #include <stdio.h>
#include <fcntl.h>
#include "unistd.h"

static int	get_lines(t_list **lines, int fd)
{
	char	*tmp;
	char	*dup;
	t_list	*node;

	*lines = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		dup = ft_strdup(tmp);
		if (!dup)
		{
			ft_lstclear(lines, free);
			free(tmp);
			return (0);
		}
		node = ft_lstnew(dup);
		if (!node)
		{
			free(dup);
			ft_lstclear(lines, free);
			return (0);
		}
		ft_lstadd_back(&(*lines), node);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (!*lines)
		return (0);
	return (1);
}

static char	**extract_file(char *file_path)
{
	int		fd;
	t_list	*lines;
	char	**ret;
	t_list	*itr;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!get_lines(&lines, fd))
		return (close(fd), NULL);
	close(fd);
	ret = malloc(sizeof(char *) * (ft_lstsize(lines) + 1));
	if (!ret)
		return (ft_lstclear(&lines, free), NULL);
	fd = 0;
	itr = lines;
	while (itr)
	{
		ret[fd++] = (char *)itr->content;
		itr = itr->next;
	}
	ret[fd] = NULL;
	ft_lstclear(&lines, NULL);
	return (ret);
}

static int	extract_info(t_map **map, char **raw_file)
{
	int	line_idx;

	if (!raw_file)
		return (-1);
	line_idx = 0;
	// split_print(raw_file);
	while (raw_file[line_idx] && raw_file[line_idx][0] != '1')
	{
		if (ft_strncmp("NO", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_NO] = get_path_direction(raw_file[line_idx]);
		else if (ft_strncmp("SO", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_SO] = get_path_direction(raw_file[line_idx]);
		else if (ft_strncmp("WE", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_WE] = get_path_direction(raw_file[line_idx]);
		else if (ft_strncmp("EA", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_EA] = get_path_direction(raw_file[line_idx]);
		else if (ft_strncmp("DO", raw_file[line_idx], 2) == 0)
			(*map)->tex[TEX_DO] = get_path_direction(raw_file[line_idx]);
		else if (raw_file[line_idx][0] == 'F')
		{
			(*map)->floor = get_colours(raw_file[line_idx]);
			if ((*map)->ceiling)
				break ;
		}
		else if (raw_file[line_idx][0] == 'C')
		{
			(*map)->ceiling = get_colours(raw_file[line_idx]);
			if ((*map)->floor)
				break ;
		}
		// else
		// 	return (-1);
		line_idx++;
	}
	if (!raw_file[line_idx])
		return (-1);
	return (line_idx);
}

static t_result	*handle_map(t_map **map, char **raw_file, int line_idx)
{
	int	size;

	if (line_idx == -1)
		return (result_error("invalid .cub file."));
	line_idx += 2;
	size = line_idx;
	// ft_printf("line_idx = [%d]\n", size);
	while (raw_file[size])
		size++;
	// ft_printf("size = [%d]\n", size);
	(*map)->y_size = (size - line_idx);
	// ft_printf("(*map)->y_size = [%d]\n", (*map)->y_size);
	(*map)->maps = malloc(sizeof(char *) * ((*map)->y_size + 1));
	if (!(*map)->maps)
		return (result_error("malloc failed"));
	size = 0;
	while (raw_file[line_idx])
	{
		if ((int)ft_strlen(raw_file[line_idx]) > (*map)->x_size)
			(*map)->x_size = ft_strlen(raw_file[line_idx]);
		(*map)->maps[size++] = ft_strdup(raw_file[line_idx++]);
	}
	(*map)->maps[size] = NULL;
	// split_print((*map)->maps);
	return (result_ok(map));
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
	// res = malloc(sizeof(t_result));
	// if (!res)
	// 	return (result_error("malloc failed"));
	map = malloc(sizeof(t_map));
	if (!map)
		return (result_error("malloc failed"));
		// return (free(res), result_error("malloc failed"));
	// ft_memset(res, 0, sizeof(t_result));
	ft_memset(map, 0, sizeof(t_map));
	raw_file = extract_file(file_path);
	if (!raw_file)
		return (result_error("invalid file format provide"));
	// extract_info(&map, raw_file);
	res = handle_map(&map, raw_file, extract_info(&map, raw_file));
	split_free((void **)raw_file);
	return (res);
}

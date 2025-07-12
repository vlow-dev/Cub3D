/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>            +#+  +:+       +#+	  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:20:45 by ialee             #+#    #+#             */
/*   Updated: 2025/07/12 21:32:08 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "./cub3d.h"
# include <stdlib.h>

typedef union s_udata
{
	t_map	*map;
	char	*err;
}	t_udata;

typedef enum e_eresult
{
	OK,
	ERROR,
}	t_eresult;

typedef struct s_result
{
	t_eresult	result;
	t_udata		data;
}	t_result;

typedef struct s_validify
{
	t_map	*map;
	int		**visited;
}	t_validify;

// result union for error handling
t_result	*result_error(char *str);
t_result	*result_ok(t_map **map);

// utility functions for handling file parsing. 
char		*unwhite(char *line);
char		*get_path_direction(char *line);
int			get_colours(char *line);
int			safe_strlen(char *str);
int			get_max_width(char **map, int *i);
int			is_valid_floor(char c);
int			is_map_valid(t_map *map);
t_result	*get_map(char *path);
int			parse_map(t_data *data, char *av);
void		free_map(t_map *map);
int			info_assign(t_map *map, char **raw_file, int line_idx);
t_result	*parse_file(char *file_path);

#endif

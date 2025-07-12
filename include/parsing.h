#ifndef PARSING_H
# define PARSING_H
# include "./cub3d.h"
# include <stdlib.h>

typedef union
{
  t_map *map;
  char *err;
} u_data;

typedef enum
{
  OK,
  ERROR,
} e_result;

typedef struct	s_result
{
  e_result result;
  u_data data;
} t_result;

typedef struct	s_validify
{
	t_map	*map;
	int		**visited;
} t_validify;

// result union for error handling
t_result  *result_error(char *str);
t_result  *result_ok(t_map **map);

// utility functions for handling file parsing. 
char		*unwhite(char *line);
char		*get_path_direction(char *line);
int			get_colours(char *line);
int			safe_strlen(char *str);
int			get_max_width(char **map, int *i);
int			is_valid_floor(char c);
int			is_map_valid(t_map *map);
t_result	*get_map(char *path);
int			parse_map(t_data *data, char* av);
void		free_map(t_map *map);

t_result  *parse_file(char *file_path);
#endif

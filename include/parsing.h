#ifndef PARSING_H
# define PARSING_H
# include "./cub3d.h"

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

// result union for error handling
t_result  *result_error(char *str);
t_result  *result_ok(t_map *map);

// utility functions for handling file parsing. 
char	  *unwhite(char *line);
char	  *get_path_direction(char *line);
int		  get_colours(char *line);

t_result  *parse_file(char *file_path);
#endif

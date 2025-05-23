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

typedef struct s_result
{
  e_result result;
  u_data data;
} t_result;

#endif

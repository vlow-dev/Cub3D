#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"
#include "../../include/parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
  t_result *x = parse_file(".cub");
  t_map *y;
  if (x->result == OK)
    y = x->data.map;
  else
  {
    printf("%s\n", x->data.err);
    return (0);
  }

  printf("%s\n", y->tex[TEX_EA]);
  printf("%s\n", y->tex[TEX_NO]);
  printf("%s\n", y->tex[TEX_SO]);
  printf("%s\n", y->tex[TEX_WE]);
  printf("%i\n", y->floor);
  printf("%i\n", y->ceiling);
  for (int i = 0; i < y->y_size; i++)
    printf("%s", y->maps[i]);
}

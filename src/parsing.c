#include "../include/cub3d.h"
#include "../libft/include/libft.h"
#include "../include/parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char **extract_file(char *file_path)
{
  int fd;
  t_list *lines;
  char *tmp;
  char **ret;

  fd = open(file_path, O_RDONLY);
  tmp = get_next_line(fd);
  lines = ft_lstnew(ft_strdup(tmp));
  while (tmp)
  {
    free(tmp);
    tmp = get_next_line(fd);
    if (tmp)
      ft_lstadd_back(&lines, ft_lstnew(ft_strdup(tmp)));
  }
  ret = malloc(sizeof(char *) * (ft_lstsize(lines) + 1));
  int i = 0;
  t_list *itr = lines;
  while (itr)
  {
    ret[i++] = (char *)itr->content;
    itr = itr->next;
  }
  ret[i] = NULL;
  ft_lstclear(&lines, NULL);
  return (ret);
}

char *unwhite(char *line)
{
  char *itr;
  int count;
  char *ret;
  char *ret_itr;

  itr = line;
  count = 0;
  while (*itr)
  {
    if (ft_isspace(*itr))
      count++;
    itr++;
  }
  ret = malloc(sizeof(char) * (ft_strlen(line) - count + 1));
  itr = line;
  ret_itr = ret;
  while (*itr)
  {
    if (ft_isspace(*itr))
    {
      itr++;
      continue;
    }
    *ret_itr++ = *itr++;
  }
  *ret_itr = '\0';
  return (ret);
}

char *get_path_direction(char *line)
{
  char *clean;

  clean = unwhite(line);
  char *ret = ft_strdup(&clean[2]);
  free(clean);
  return ret;
}

int get_colours(char *line)
{
  char *clean;
  char **rgb;
  int i;
  char **rgb_itr;
  int *j;

  clean = unwhite(line);
  rgb = ft_split(&clean[1], ',');
  rgb_itr = rgb;
  j = malloc(sizeof(int) * 4);
  i = 1;
  while (*(++rgb_itr))
    i++;
  if (i != 3)
    return (-1);
  j[0] = ft_atoi(rgb[0]);
  j[1] = ft_atoi(rgb[1]);
  j[2] = ft_atoi(rgb[2]);
  if ((j[0] < 0 || j[0] > 255) && (j[1] < 0 || j[1] > 255) && \
    (j[2] < 0 || j[0] > 255))
  {
    free(j);
    free(clean);
    return (-1);
  }
  i = (j[0] << 16 | j[1] << 8 | j[2]);
  free(rgb);
  free(j);
  free(clean);
  return (i);
}

int extract_info(t_map **map, char **raw_file)
{
  int line_idx;

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

t_result *result_error(char *str)
{
  t_result *res;

  res = malloc(sizeof(t_result));
  res->result = ERROR;
  res->data.err = ft_strdup(str);
  return (res);
}

t_result *result_ok(t_map *map)
{
  t_result *res;

  res = malloc(sizeof(t_result));
  res->result = OK;
  res->data.map = map;
  return (res);
}

t_result *handle_map(t_map **map, char **raw_file, int line_idx)
{
  int size;

  if (line_idx == -1)
    return (result_error(".cub file does not contain definition of map layout."));
  size = line_idx;
  while(raw_file[size])
    size++;
  (*map)->y_size = (size - line_idx);
  (*map)->maps = malloc(sizeof(char *) * (*map)->y_size + 1);
  size = 0;
  while(raw_file[line_idx])
    (*map)->maps[size++] = ft_strdup(raw_file[line_idx++]);
  (*map)->maps[size] = NULL;
  return (result_ok(*map));
}

t_result *parse_file(char *file_path)
{
  t_map *map;
  char **raw_file;
  t_result *res;
  int leng;

  leng = ft_strlen(file_path);
  if (ft_strlen(file_path) <= 4 || ft_strncmp(".cub", &file_path[leng - 4], 4))
    return (result_error("file provided is not a .cub file"));
  res = malloc(sizeof(t_result));
  map = malloc(sizeof(t_map));
  raw_file = extract_file(file_path);
  extract_info(&map, raw_file);
  res = handle_map(&map, raw_file, extract_info(&map,raw_file));
  return (res);
}

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

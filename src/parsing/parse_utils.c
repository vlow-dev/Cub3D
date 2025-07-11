#include "cub3d.h"
#include "parsing.h"

bool	is_valid_extension(char *filename, char *extension)
{
	int	len_file;
	int	len_ext;

	len_file = ft_strlen(filename);
	if (filename[len_file - 1] == '\n')
		len_file--;
	len_ext = ft_strlen(extension);
	if (len_file < len_ext)
		return (false);
	filename += len_file - len_ext;
	if (ft_strncmp(filename, extension, len_ext) == 0)
		return (true);
	return (false);
}

bool	is_valid_file(char *file)
{
	int	fd;

	if (is_valid_extension(file, ".cub") == false)
	{
		ft_putstr_fd("Error\nInvalid file type\n", 2);
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nInvalid file\n", 2);
		return (false);
	}
	close(fd);
	return (true);
}

bool	is_texture_filled(t_texture tex)
{
	if (tex.no_tex.path == NULL
		|| tex.so_tex.path == NULL
		|| tex.we_tex.path == NULL
		|| tex.ea_tex.path == NULL
		|| tex.ceiling.is_set == false
		|| tex.floor.is_set == false)
	{
		ft_putstr_fd("Error\nOne or more texture/color not filled\n", 2);
		return (false);
	}
	return (true);
}

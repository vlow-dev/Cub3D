#include "cub3d.h"
#include "cub3d.h"

bool	is_valid_color_str(char *str)
{
	int	comma_count;

	comma_count = 0;
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0 && ft_isspace(*str) == 0 && *str != ',')
		{
			return (false);
		}
		if (*str == ',')
			comma_count++;
		str++;
	}
	if (comma_count != 2)
	{
		return (false);
	}
	return (true);
}

void	is_valid_color(char *str, char **is_err)
{
	while (ft_isspace(*str) == 1)
		str++;
	if (!is_valid_color_str(str))
		is_err = ft_strdup("Error: Invalid color string.");
}

void	is_valid_color_range(int *rgb, char **is_err)
{
	if (rgb[0] < 0 || rgb[0] > 255
		|| rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
	{
		*is_err = ft_strdup("Error: Invalid color value ranges\n");
	}
}

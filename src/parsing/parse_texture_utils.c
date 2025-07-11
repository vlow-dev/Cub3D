#include "cub3d.h"
#include "cub3d.h"

char	*ft_strndup(char *str, int len)
{
	char	*new_str;
	int		i;

	new_str = malloc((len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (*str != '\0' && len > 0)
	{
		new_str[i] = *str;
		i++;
		str++;
		len--;
	}
	new_str[i] = '\0';
	return (new_str);
}

bool	is_valid_texture(char *str, t_tex_img *tex_img, int *is_err)
{
	if (tex_img->path != NULL)
	{
		ft_putstr_fd("Error\nTexture assigned\n", 2);
		*is_err = 1;
		return (false);
	}
	while (ft_isspace(*str) == 1)
		str++;
	if (is_valid_extension(str, ".xpm") == false)
	{
		ft_putstr_fd("Error\nInvalid texture file\n", 2);
		*is_err = 1;
		return (false);
	}
	return (true);
}

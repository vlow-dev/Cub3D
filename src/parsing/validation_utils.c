/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:34 by ialee             #+#    #+#             */
/*   Updated: 2025/06/27 15:28:29 by ialee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	get_max_width(char **map, int *i)
{
	int	current_width;
	int	ret;

	*i = 0;
	ret = 0;
	while (map[*i])
	{
		current_width = safe_strlen(map[*i]);
		if (current_width > ret)
			ret = current_width;
		(*i)++;
	}
	return (ret);
}

int	is_valid_floor(char c)
{
	return (c == '0' || c == 'N'
		|| c == 'S' || c == 'E'
		|| c == 'W');
}

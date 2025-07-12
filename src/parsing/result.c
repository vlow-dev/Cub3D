/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialee <ialee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:34 by ialee             #+#    #+#             */
/*   Updated: 2025/07/12 21:38:26 by vlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../libft/include/libft.h"
#include "../../include/parsing.h"
#include <stdlib.h>
#include <fcntl.h>

t_result	*result_error(char *str)
{
	t_result	*res;

	res = malloc(sizeof(t_result));
	if (!res)
		return (NULL);
	ft_memset(res, 0, sizeof(t_result));
	res->result = ERROR;
	res->data.err = ft_strdup(str);
	if (!res->data.err)
		return (free(res), NULL);
	return (res);
}

t_result	*result_ok(t_map **map)
{
	t_result	*res;

	res = malloc(sizeof(t_result));
	if (!res)
	{
		free_map(*map);
		return (malloc(0));
	}
	ft_memset(res, 0, sizeof(t_result));
	res->result = OK;
	res->data.map = *map;
	return (res);
}

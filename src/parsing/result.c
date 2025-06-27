/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlow <vlow@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:34 by vlow              #+#    #+#             */
/*   Updated: 2025/06/27 12:27:35 by vlow             ###   ########.fr       */
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
	res->result = ERROR;
	res->data.err = ft_strdup(str);
	res->data.map = NULL;
	return (res);
}

t_result	*result_ok(t_map *map)
{
	t_result	*res;

	res = malloc(sizeof(t_result));
	res->result = OK;
	res->data.map = map;
	res->data.err = NULL;
	return (res);
}
